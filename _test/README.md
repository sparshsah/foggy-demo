# unit tests

Documented minimal working examples of unit tests in different languages,
trying to provide a "template" for universal core unit-test functionality
while following each language's particular idioms/conventions.

I like to put unit tests in a separate directory (usually named something like `_test`)
that lives at the top level (next to the source directory) and mirrors the
internal structure of the source directory.

For example, if I have a repository `my-module` with
source code in `my-module/my_module/my_submodule/my_submodule.py`, I'll put
unit tests in `my-module/_test/my_submodule/test_my_submodule.py`.

Similarly if I have a repository `my-app` with source code in
`my-app/MyApp/Model/BaseModel.swift`, I'll put unit tests in
`my-app/MyAppTests/Model/BaseModelTests.swift`.

Of course, first and foremost is to follow the conventions of your
particular language, environment, and team. For example,
Xcode "likes" a particular default workspace structure for iOS apps.
And I'm not going to argue with Apple about how to work within
their own ecosystem.
