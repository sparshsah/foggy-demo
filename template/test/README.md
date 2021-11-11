# unit tests

Documented minimal working examples of unit tests in different languages,
trying to provide a "template" for universal core unit-test functionality
while following each language's particular idioms/conventions.

## to colocate or not to colocate?

I like to put unit tests in a separate directory (usually named something like `_test`)
that lives at the top level (next to the source directory) and mirrors the
internal structure of the source directory.

For example, if I have a repository `my-module` with
source code in `my-module/my_module/my_submodule/my_submodule.py`, I'll put
unit tests in `my-module/_test/my_submodule/test_my_submodule.py`.

There is a great debate between people who like to put their unit tests
in a separate directory and people who like to colocate their
unit tests, either literally right next to the target source code (e.g.
in `my-module/my_module/my_submodule/test_my_submodule.py`) or
in a self-contained subdirectory (e.g. in
`my-module/my_module/my_submodule/_test/test_my_submodule.py`).
One compelling argument for this is that at the end of the day,
how you choose to organize your code into "modules" or "apps"
or "repositories" is a bit arbitrary: For example, if your company's
code is organized into multiple repositories, should you go to the logical
extreme and create entire new repositories to store unit-test code?
Proponents of this argument point out that colocating unit tests
makes your organizational structure self-consistent at every level
of the hierarchy. I actually find this argument pretty compelling,
but more experienced programmers have convinced me that in practice,
the advantage of being able to cleanly separate out source code
from unit tests and/or demos outweighs the slight "inelegance".
For example, you might not always want to include unit tests in
your released app, for size or security reasons.
I don't consider myself qualified enough to have an opinion,
so I defer to theirs.

Of course, first and foremost is to follow the conventions of your
particular language, environment, and team. For example, as far as I can tell,
Xcode "likes" a particular default workspace structure for iOS apps.
And I'm not going to argue with Apple about how to work within
their own ecosystem. So for example,
if I have a repository `my-app` with source code in
`my-app/MyApp/Model/BaseModel.swift`, I'll put unit tests in
`my-app/MyAppTests/Model/BaseModelTests.swift`.

## "fuzzing" instead of writing explicit unit tests

TODO(sparshsah): more to come..

## obviating unit tests altogether

And zero-th and foremost: Assertions! `assert` and related statements
(for example Swift's `precondition`) are a convenient tool for
enforcing preconditions, checking loop invariants, or even just
unequivocally documenting your intentions. Plus, mainstream compilers offer an
"optimized" mode that can strip out assertions for you, so you can rest
assured you won't be forced to ship code that's bogged down
with "too many" assertions. (Personal note: I don't think there's any
such thing as "too many" assertions. But I can understand why a
consumer-app developer might disagree.)
