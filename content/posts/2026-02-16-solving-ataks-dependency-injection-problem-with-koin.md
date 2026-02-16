---
title: Solving ATAK's Dependency Injection Problem with Koin
date: 2026-02-16
draft: false
---

HI, it's been a second since i posted. but recently the powers that be have given me a long weekend and after two days of bedrotting, i came to a crazy realization. instead of defaulting to a factory pattern or spamming global singletons in ATAK, we can just use Koin - just not how most android apps would LOL.

## the problem

as we all know, ATAK plugins have issues accessing the standard android app lifecycle, this makes making implementation of standard android classes pretty difficult, so implementing a `ViewModel()` just doesn't work. So we can kiss goodbye to things that a normal android view model could technically do, things like the `viewModelScope`, automatic lifecycle-aware coroutine cancellation, configuration-change resillience, blah blah blah you get the point. this makes it so that we need to do more manual work in atak plugins.

this problem becomes a really big headache when we need external libraries in our ATAK plugins since a lot of standard android depdendencies need `Context`, for more info check out [my previous post on context in ATAK](https://zainraza.net/posts/2024-09-08-fixing-atak-for-android-devs/#what-the-context). something that can be a difficult thing to get working depending on the library, and this extends to all the standard DI libraries: Dagger/Hilt and Koin-Android are basically impossible to setup as of right now in ATAK. BUT i had a stupid but simple realization: _what if we just used koin-core instead of koin-android?_

## how this would solve it

koin-core is meant for standard kotlin applications, not android apps, so if we retrofit (haha get it) it for "android" use, so there is no need for `Context`, this logic also applies to any library that offers a core version instead of an android version, even though some libraries will definitely work is you pass in the `appContext` and not the `pluginContext`.

## setup tutorial

for future readers' sake, this tutorial was made in ATAK-CIV `5.6.0.13`.if you want to skip the tutorial and look at a simple example, i committed [this project to my github](https://github.com/zainaraza43/atak-dependency-injection-example)

## gradle

anyways, let's setup the gradle dependency. in your app level build.grade, add this line to your dependencies block.

```groovy
implementation 'io.insert-koin:koin-core:$koin_version' // as of rn im using 4.1.1
```

## the setup classes

for this i'm following the [koin tutorial](https://insert-koin.io/docs/quickstart/kotlin) with some minor changes.

data class:

```kotlin
data class User(val name: String, val email: String)
```

repository:

```kotlin
interface UserRepository {
    fun findUserOrNull(name: String): User?
    fun addUsers(users: List<User>)
}

class UserRepositoryImpl : UserRepository {

    private val _users = arrayListOf<User>()

    override fun findUserOrNull(name: String): User? {
        return _users.firstOrNull { it.name == name }
    }

    override fun addUsers(users: List<User>) {
        _users.addAll(users)
    }
}
```

service:

```kotlin
interface UserService {
    fun getUserOrNull(name: String): User?
    fun loadUsers()
    fun prepareHelloMessage(user: User?): String
}

class UserServiceImpl(
    private val userRepository: UserRepository
) : UserService {

    override fun getUserOrNull(name: String): User? = userRepository.findUserOrNull(name)

    override fun loadUsers() {
        userRepository.addUsers(listOf(
            User("Alice", "alice@example.com"),
            User("Bob", "bob@example.com"),
            User("Charlie", "charlie@example.com")
        ))
    }

    override fun prepareHelloMessage(user: User?): String {
        return user?.let { "Hello '${user.name}' (${user.email})! 👋" } ?: "❌ User not found"
    }
}
```

view model:

```kotlin
class UserViewModel(private val userService: UserService) {

    init {
        userService.loadUsers()
    }

    fun sayHello(name: String): String {
        val user = userService.getUserOrNull(name)
        val message = userService.prepareHelloMessage(user)
        return "[UserViewModel] $message"
    }
}
```

## the module

here we want to define a global app module so that we can inject wherever we want, notice that we are defining all of these classes as `single`, even the view model, because in ATAK, the view model isn't actually a special class at all.

```kotlin
val appModule = module {
    single<UserRepository> { UserRepositoryImpl() }
    single<UserService> { UserServiceImpl(get()) }
    single { UserViewModel(get()) }
}
```

## instantiation

now in the `init { }` block, we can add the `startKoin { }` block:

```kotlin
init {
        startKoin {
            modules(appModule)
        }
        ...
}
```

and now we can instantiate our view model like this in every class other than `PluginTemplate`:

```kotlin
private val userViewModel = KoinPlatform.getKoin().get<UserViewModel>()
```

but since i'm doing this in the `PluginTemplate` class i'm going to need to use the `lateinit var` variation, since insantiating the variable before the `init { }` block is run will break our plugin in runtime.

```kotlin
private lateinit var userViewModel: UserViewModel
```

```kotlin
override fun onStart() {
        // the plugin is starting, add the button to the toolbar
        if (uiService == null) return

        uiService!!.addToolbarItem(toolbarItem)

        userViewModel = KoinPlatform.getKoin().get<UserViewModel>()
        Log.i("PluginTemplate", userViewModel.sayHello("Alice"))
    }
```

### testing

now when we install the plugin we can see under the `PluginTemplate` tag:

```
2026-02-16 15:09:00.216 22611-22611 PluginTemplate          com.atakmap.app.civ                  I  [UserViewModel] Hello 'Alice' (alice@example.com)! 👋
```

now we can successfully inject our dependencies instead of passing them in as global singletons everywhere, or even worse, manually making factories for instantiation 🤮
