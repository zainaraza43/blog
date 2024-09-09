---
title: Fixing ATAK for Android Devs
date: 2024-09-08
draft: false
---

if you have ever developed in Android and had the misfortune of being assigned to an ATAK plugin and thought "what the f$%& am i looking at..." well you're in great company! ATAK is possibly the strangest, least documented, lamest "framework" that i have had the displeasure of working with. that being said, i've been on ATAK plugin projects for almost all of this calendar year and have picked up some useful pieces of information that aren't documented anywhere on the internet except for in atak's discord community.

**note all of these techniques are current to ATAK 5.1.0+ things can change**

## what this is

i'm going to show how i personally develop atak plugins, how i implement common design patterns, how i get over ATAK's "isms" and my philosophy of building things regardless of ATAK's many limits.

## what this isn't

i will not be explaining ATAK plugins in intro level detail, the assumption is that you know the difference between a `MapComponent` and a `DropDownReceiver`. also if you use java you may be sol but it isn't too hard to convert out of kotlin. if you're looking for something more intro level take a look at [RIIS's blog post about ATAK plugins](https://www.riis.com/blog/atak-plugins-part-1) that i helped write.

## how to instantiate classes

regardless of architecture/design pattern you would like to enforce, you'll probably be wondering: how do i instantiate key services, view models, and other important classes? the typical answer is to use some library like Dagger/Hilt to do some dependency injection. now i personally have spent many hours and days into getting this to work but unfortunately my efforts were futile. so until someone shows me a working dependency injection tool for ATAK, the answer is to declare your important classes at the top of your `MapComponent` as `lateinit var` and then instantiate at the top of the `onCreate` function.

```kt
class MapComponent : DropDownMapComponent() {
    
    ...

    private lateinit var db: Database
    private lateinit var repository: Repository
    private lateinit var viewModel: ViewModel

    override fun onCreate(
        context: Context, 
        intent: Intent,
        view: MapView
    ) {

        ...

        db = Database.getInstance(context = view.context)
        repository = RepositoryImp(database = db)
        viewModel = DroneViewModel(repository = repository)
    }
}
```

## what the context

you'll notice that for application context i pass in `view.context`, that's because the biggest and most obvious limitation of ATAK plugins is the lack of an Android `Activity` and therefore the whole traditional lifecycle kind of gets thrown out. as a consequence of no Activities, we have a lot of libraries that won't work, `Fragments` don't work, neither do traditional `ViewModels`, you'll notice that when i instantiated my view model, i didn't use `ViewModel()` but instead made a custom class that acts like a View Model to perserve MVVM. the best we have is `view.context` which will act as our `ApplicationContext` with some limitations.

## mvvm

honestly now that you know those two things, the sky is kinda the limit, but i'll show you how i do mvvm since that's the design pattern i prefer with most xml based projects like ATAK plugins generally are. as a side note you can try using compose, however it lacks support and tbh the last time i tried using it, it did not work at all, but i didn't spend enoungh time trying to figure that out.


### view models

anyways here's what a normal view model looks like as i implement it:

```kotlin
class SomeViewModel(
    someRepository: SomeRepository
)

    val something = someRepository.something

    fun updateSomething(something: Something) {
        CoroutineScope(Dispatchers.IO).launch {
            someRepository.updateSomething(something)
        }
    }
```

now this is just a class that mocks what a view model would typically do however it does get the job done for the most part. using the io threads until i can't in which case i will use `withContext(Dispatchers.Main)`.


### repositories

these are very standard, just no DI which we're all used to.

```kotlin
interface SomeRepository {

    val something: StateFlow<Something>

    suspend fun updateSomething(something: Something)
}
```

```kotlin
class SomeRepositoryImp (
    private val database: Database
) : SomeRepository {

    private val _something = MutableStateFlow(idk something)
    override val something = _something.asStateFlow()

    override suspend fun updateSomething(something: Something) {
        _something.emit(something)
    }

}
```

### databases

i typically use `Room` which requires `ksp`, which can be kinda annoying to import into your ATAK project, specifically because it depends on your kotlin version. since i'm currently writing this on atak 5.1.0, i'm using kotlin `1.9.25` so i scroll on the [release list](https://github.com/google/ksp/releases?page=1) of ksp that supports my kotlin version. That ends up being 2.6.1 that looks like this in my app level dependencies block:

```gradle
dependencies {
    implementation "androidx.room:room-runtime:2.6.1"
    ksp "androidx.room:room-compiler:2.6.1"
    implementation "androidx.room:room-ktx:2.6.1"
}
```

now you can use room as you please, add converters, instantiate your database and do whatever you want with that.

## summary

using ATAK has fried my brain but hopefully with the above tips its more human to write and maintain code. 