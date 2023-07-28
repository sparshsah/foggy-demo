# The OrgChart at a Well-Functioning Financial-Sector Firm

Roles and two ways to get fired in each: Doing too little, or Doing too much.
Made in response to repeated questioning from my friends who have decided to
give in and jump on the hedge-fund bandwagon,
asking me as one of the ones who never resisted and just got on voluntarily on day 1.
Scroll down to your relevant level.

## Level 0: Intern
* The role: Pretty much, come up with one main finished deliverable by the end of the summer.
* How to get fired (or, I guess, more like, "not get a return offer"):
  * Doing too little: This one's obvious.
    Some Interns for one reason or another clearly don't need or want the return offer,
    and are basically there as a paid summer camp.
  * Doing too much: This one is a more nuanced pitfall.
    Most intern-project ideas were solicited and chosen months ago,
    but then assigned to fresh-faced managers,
    because senior managers are too busy to deal with an intern.
    These fresh-faced managers are bright and full of energy,
    and have invariably spent the last three weeks fiddling with and adding to your project spec.
    In principle your mentor's role is to guide you through that project spec
    and also act as an interface between you and your manager,
    but keep in mind that the mentors are going to be junior researchers with no management experience.
    There's nothing wrong with that per se, but it does mean that in practice they
    (a) don't know what the fuck they're doing themselves, plus
    (b) are too cowardly to speak up when the manager
    (who stopped being an individual-contributor a year ago and automatically forgot what doing actual work is like)
    has become way too ambitious with the spec for a ten-week intership.
    For the good of both you (who want a return offer) and your manager (who wants a successful intern,
    partly for street cred and partly because they're often relying on hiring you to fill open headcount on their team),
    you must as soon as possible choose one main coherent thing out of the project spec and commit to,
    at the very least, putting together a finalized, correct deck on that,
    and being able to confidently answer questions about it during the presentation.

## Level 1: Analyst
* The role: Produce correct and useful answers to the questions your VP assigns you.
* How to get fired:
  * Doing too little: You are the "boots on the ground".
    You need to be able to exercise judgment and make recommendations to your VP
    about what the most promising way to proceed is, or alternatively, if this seems like a dead end.
    Don't make your VP have to babysit you.
    Making your VP sit through 100-slide decks enumerating every piece of information you generated
    seems like holding yourself accountable, but in reality it's a (a) a waste of your VP's time,
    and (b) not even a useful waste of time, because they have learned nothing from it.
    Like you, they are humans, not computers: You need to compile and synthesize your information
    into an actual direct and intelligible answer to their question.
  * Doing too much: Make an error out of negligence.
    Nobody expects you to be perfect, and we all make mistakes.
    But it is better to have five things that are right,
    than to have ten things that are right plus one that thing is wrong.
    In asset management, having five +10% years in a row is better than
    having four +20% years in a row followed by a -20% year.
    Even accounting for geometric compounding, the latter manager is still beating the former --
    But nobody cares, because you've shaken their faith in you and they've taken their assets elsewhere.
    This is not to say you're alone in the dark:
    When you're an Analyst your VP is going to be happy to help sanity-check your work,
    so while mistakes like "I forgot that XYZ country uses different trading hours"
    or even "I used the wrong cash series when compounding my excess returns"
    might seem silly, they happen all the time and it's fine
    (I mean, correct it once it's discovered, but it's fine).
    But compare that to a mistake like
    "I blindly copy-pasted a tcost model from the Internet then
    ignored the NumPy warnings when I ran the code because the numbers seemed to come out fine,
    and therefore produced results that not only
    use the wrong tcost model, but also don't even use that wrong model
    correctly because the code I copy-pasted wasn't expecting NaN's".
    The latter error is pure---almost willful---negligence, and
    even though as an Analyst you're not at the level
    where mistakes like that can cause a -20% year for the fund,
    from that moment onward everyone is going to think of you as the person who,
    _if promoted to that level_, would pose a real risk of causing such a year.
    (Sidenote here: Errors that cause overleverage of losing positions,
    as in [AXA Rosenberg's SEC case](https://www.sec.gov/news/press/2011/2011-37.htm),
    are even worse than errors that cause underleverage of winning positions.
    It may seem arbitrary, but it's the difference between "more negative" and "less positive".
    The latter means you just didn't make as much money as you were supposed to,
    while the former means you lost more money than you were supposed to.)

## Level 2: Associate
* The role: Do whatever your MD wants.
* How to get fired:
  * Doing too little: Continue to be an Analyst.
    That means simply waiting passively for questions.
    By this level you should be able to proactively understand the overall team agenda.
    At least once a month, your MD will walk by your desk,
    out-of-left-field make a vague reference to something you might or might not have worked on once,
    ask you to remind them what the results of this amorphous potential project were,
    and then wonder aloud whether it could be useful to this thing your team's Partner wants.
    They will then notice their lunch has arrived, tell you that you guys should catch up on this later,
    and then spend the rest of the day in meetings, completely forgetting what they asked you.
    It sounds silly, but in reality if you understand the overall team agenda, 8 times out of 10
    you will be able to fill in the blanks and infer what your MD was talking about,
    and then dust off those results, maybe polish them up a bit, and send a him/her a summary.
  * Doing too much: Disagree with your MD. Sorry, it's true.
    Analysts have free rein (and should) to push back on what their VP's think,
    because the VP him/herself is anxious to produce good results,
    and the only way they can produce good results is by taking credit for yours,
    and the only way yours will be worth taking credit for is if they've been thoughtfully-produced.
    In fact, Analysts can even disagree with MD's, because nobody pays attention to what an Analyst says.
    Associates on the other hand are in an awkward middle ground where they're
    important enough that people will remember them if they speak out-of-turn,
    but not yet important enough to have the right to disagree with MD's,
    whose credentials and title have made them
    fearless and quite frankly a little too thick for their own good.
    The right move here is to privately complain to your VP,
    and then let _your VP_ go argue with the MD.

## Level 3: Vice President
* The role: Delegate tasks to your Analysts, make sure they have the resources they need to complete them,
  and then take credit for their results at the cost of also bearing blame for their mistakes.
* How to get fired:
  * Doing too little: This is more common among newer VP's.
    You basically end up becoming a simple conduit for agenda items to flow from your Partner or MD to your Analyst,
    and then spend most of your time micromanaging the hell out of the Analyst(s) you assigned to do them.
    If this happens, take a step back and make sure that you're adding value in the chain (i.e.
    manage timelines so that people get assigned to the right project at the right time, and
    prioritize agenda items so that important stuff gets done first --
    this latter is especially tricky because, unless pushed for an answer, Partners do not distinguish
    actual mission-critical agenda items from random sidethoughts that popped into their head 30 seconds ago).
    If you're not adding that value, your Partner or MD will get impatient that things aren't going smoothly,
    and start going directly to your Analyst with questions. Once this happens it's game-over for you.
    At the end of the year, when your Partner asks you why
    your five-analyst team accomplished only the work of a four-analyst team,
    you will want to---but not have the guts to!---say,
    "because you took up all the fifth guy's time with your own stuff".
  * Doing too much: Spend all your time chasing your own bright ideas.
    The firm is paying you to make the Analysts productive, not be the ideas-guy.
    (And quite frankly, nobody gives a shit about your ideas, except maybe your MD who will steal any good ones.)

## Level 4: Senior Vice President / Executive Director
* This is a ceremonial title. You are still a VP.

## Level 5: Managing Director
* The role: Be an overall self-aggrandizing egomaniac and spiral deeper into a desperate frenzy
  as you wait for lightning to strike (a new fund, a big client, etc) so you can make Partner.
* How to get fired:
  * Doing too little: Honestly unfortunate but if you maintain a low profile
    and spend most of your time helping your team run smoothly,
    people at the top will start to wonder why they're paying MD comp for VP labor.
  * Doing too much: Very delicate balance here.
    If you start to run too _high_ a profile before you're ready to maintain it,
    you risk attracting the attention of a more-favored MD who will
    become intrigued by the activity they see going on in your department,
    and ask to take it over.

## Level 6: Partner (followed by Executive Partner, followed by Managing Partner)
* I have no clue what goes on at this level, other than the fact that
  it seems like at this stage, when you have a lot of research experience,
  and business context, and people respect your ideas,
  you are assigned to immediately stop doing any research
  and instead spend all your time flying out to meet clients.
  I have literally had to help a Partner set up a brand-new workspace like I was onboarding an intern,
  because they really wanted to try some research idea
  but their Dev Environment was completely broken as it hadn't been updated since they got promoted three years ago.
