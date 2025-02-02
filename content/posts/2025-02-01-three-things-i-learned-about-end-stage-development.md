---
title: Three Things I Learned About End Stage Development
date: 2025-02-01
draft: true
---

i've been working as a software engineer for about two years now and although i'm relatively new to the field, i've learned a lot about how we build software for production use. since i work at a software consultancy, we often don't have the opportunity to see a project all the way through from beginning to end. typically we are thrown in at some random point and told to complete a part of a project or give clients proof of concepts. but over the second half of 2024 and going into 2025, i've started and almost completed delivery of a project and the biggest concepts (technical and non-technical) i've had to learn are all about end stage development/delivery of a project.


## nothing really works as intended

this is kind of a hyperbole, but through extensive QA, you'll quickly find that there are states, conditions, variables, functions, and much more that are being triggered from the wildest places. specifically i remember plugging up a ton of race conditions that i didn't even think were possible during initial development. another mistake i made was naively believing that `null` conditions and variables would not be as big of a deal as they were, especially when you're working with UI elements, ALL conditions need to be handled, even things that you think are safe from being null, like the date/time, the user's name, and other things that you would expect that we would always have a record for if we're displaying are not as safe as you think they are. of course, this is going to be project and code specific, however i think that when you're building out that feature to display the user's name or something very basic, it could make sense to think if the following might make sense.

```kotlin
data class Profile(
      val username: String?
      val email: String?
      val createdAt: LocalDateTime?
)

fun isProfileValid(profile: Profile): Boolean {
      return profile.username?.isNotBlank() == true &&
             profile.email?.isNotBlank() == true &&
             profile.createdAt != null
}
```

this is a simple example of a function we can all use to make sure we're definitely not going to throw a `NullPointerException` or something similar later which would've been entirely avoidable, and it looks really stupid to forget but i assure you that when us programmers are blasting away at finishing a feature, we often forget these simple things, and small issues like this can snowball into day long bugs where you're going down the entire stack trace just to find that at registration, `email` somehow was `null`.
