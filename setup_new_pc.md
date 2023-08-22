# macOS

0. Set dock location to LHS of screen
1. Turn off fucking AutoCorrect
    * System Settings > Keyboard > Input Sources > Edit > Correct Spelling Automatically
    * System Settings > Keyboard > Input Sources > Text Replacements
2. Install XCode Command Line Tools with `xcode-select --install`
3. Create a `.zshrc` with `touch ~/.zshrc`
4. [Generate a new SSH key](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent)
5. Tell zsh to automatically activate it at startup by adding the following to your `~/.zshrc`: `ssh-add --apple-load-keychain`
5. [Add it to GitHub](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/adding-a-new-ssh-key-to-your-github-account)
6. Add GitHub to known hosts `ssh-keyscan github.com >> ~/.ssh/known_hosts`
7. `mkdir` your directory structure, and `git clone` whatever repos you want
8. [Install Anaconda](https://docs.anaconda.com/free/anaconda/install/mac-os.html)
    * You can keep it up-to-date [as follows](https://www.anaconda.com/blog/keeping-anaconda-date)
    * [Create a new Python venv](https://docs.conda.io/projects/conda/en/latest/commands/create.html) with `conda create --name=py_venv python=3.xx anaconda` (replace `xx` with the desired version)
    * Tell zsh to automatically activate it at startup by adding the following to your `~/.zshrc`: `conda activate py_venv`
    * You can upgrade Python every once in a while with `conda deactivate && conda remove --name=py_venv --all && conda create --name=py_venv python=3.xx anaconda`
9. Prepend to your PATH by adding the following to your `~/.zshrc`: `export PATH=/path/to/your/code:/path/to/more/code:$PATH`
11. [Install VSCode](https://code.visualstudio.com/download), optionally turning on Settings Sync and opening your notes doc
12. (optional) Set Safari to your favorite tabs: YouTube Music, Google Drive, Gmail, Amazon Prime Video, and Disney+
13. (optional) Install iMovie from the App Store
