# macOS

1. Install XCode Command Line Tools with `xcode-select --install`
2. [Generate a new SSH key](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent)
3. [Add it to GitHub](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/adding-a-new-ssh-key-to-your-github-account)
4. Add GitHub to known hosts `ssh-keyscan github.com >> ~/.ssh/known_hosts`
5. `mkdir` your directory structure, and `git clone` whatever repos you want
6. [Install Anaconda](https://docs.anaconda.com/free/anaconda/install/mac-os.html)
    * You can keep it up-to-date [as follows](https://www.anaconda.com/blog/keeping-anaconda-date)
    * [Create a new Python venv](https://docs.conda.io/projects/conda/en/latest/commands/create.html) with `conda create --name=py python=3.xx anaconda && conda activate py`
7. Prepend to your PATH by adding the following at the bottom of your `~/.zshrc`: `export PATH=/path/to/your/code:/path/to/more/code:$PATH`
