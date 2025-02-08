---
title: Three Things I Learned About End Stage Development
date: 2025-02-08
draft: false 
---

i've been working as a software engineer for about two years now and although i'm relatively new to the field, i've learned a lot about how we build software for production use. since i work at a software consultancy, we often don't have the opportunity to see a project all the way through from beginning to end. typically we are thrown in at some random point and told to complete a part of a project or give clients proof of concepts. but over the second half of 2024 and going into 2025, i've started and almost completed delivery of a project and the biggest concepts (technical and non-technical) i've had to learn are all about end stage development/delivery of a project.


## nothing really works as intended

this is kind of a hyperbole, but through extensive QA, you'll quickly find that there are states, conditions, variables, functions, and much more that are being triggered from the wildest places. specifically, i remember plugging up a ton of race conditions that i didn't even think were possible during initial development. another mistake i made was naively believing that `null` conditions and variables would not be as big of a deal as they were, especially when you're working with UI elements, ALL conditions need to be handled, even things that you think are safe from being null, like the date/time, the user's name, and other things that you would expect that we would always have a record for if we're displaying are not as safe as you think they are. of course, this is going to be project and code specific, however i think that when you're building out that feature to display the user's name or something very basic, it could make sense to think if the following might make sense.

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

## constant communication is necessary

i've seen a lot of complaints about the daily standup and there are a lot of great criticisms about scrum/agile, but the one thing people won't complain about is whether people are on the same page or not which according to the agile manifesto is the main reason it was ever created, to make sure all stakeholders as involved as possible so that we can adapt on the fly as easily as possible. some of the issues i've faced are because we didn't have systems like a daily standup and the best way to contact the client was through email so we, through no fault of our own, would make micro decisions on our own so that we weren't stuck waiting on an email that could take a lot of billable time to get back to us, these kinds of decisions ended up costing us a lot when we did end up bridging the communication gap with a revolving meeting with decision makers and a shared group chat for good decision making.

## the buck stops with you

the unfortunate reality is that if you're the main or lead dev on a project that regardless of who's *fault* it is that the project failed, it was mostly your responsibility to get it over the line. this lesson was definitely the most difficult to swallow for me in large part i felt like a lot of shit happened between me working and the project failing, but to be honest as far as the business is concerned, bottom line the project either made the deadline and was "successful" or it didn't, no one really cares that nobody was helpful defining the criteria, or that important stakeholders were off on vacation whilst you were struggling, either flag that as a huge problem and communicate it or don't be surprised with the consequences. if someone made an unreasonable estimate/promise, all you can do is your best and communicate your frustrations. sometimes all we can do is give our best effort when dealt a poor hand but in a weird way, that kind of experience makes you a little bit tougher, and that can be a good thing.
