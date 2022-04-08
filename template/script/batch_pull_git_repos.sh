#!/bin/bash

# author: sparshsah

# system/user-specific global constants, set this block as appropriate
ORIGIN="origin"
# market leader GitHub has switched its default branch name, but not all devs have accepted
MAIN="main"
LOCAL_REPO_PATH="/code/$(id -u -n)/"  # e.g. "/code/sparshsah/"
EXCL_REPO_NAMES=("data-dump-folder/" "some-legacy-lib/" "another-legacy-lib/")
I_AM_LEET_HACKERMAN=false

# directory names end in "/"
REPO_NAMES=$(ls "$LOCAL_REPO_PATH" | grep "/")


prompt_until_yes() {
  echo "$1, ok? ('y' to proceed [if possible else skip], 'Ctrl+C' to quit)"
  CONFIRM_INPUT="n"
  while [[ "$CONFIRM_INPUT" != "y" ]]; do
    read CONFIRM_INPUT
  done
}

exec_except_prompt() {
  $@ || prompt_until_yes "..error executing '$*' (exit status code $?, recommend quitting to debug)"
}

git_checkout_main() {
  git checkout "$MAIN" || git checkout main || git checkout master
}

git_checkout_main_and_pull() {
  echo "..switching to main and pulling.."
  # TODO(sparshsah): why can't i just use `(checkout && pull)` or `{ checkout && pull; }`?
  exec_except_prompt git_checkout_main
  exec_except_prompt git pull
}

prompt_if_head_is_off_main() {
  BRANCH=$(git symbolic-ref --short HEAD)
  [[ "$BRANCH" != "$MAIN" ]] && prompt_until_yes "..HEAD \`$BRANCH\` is off main \`$MAIN\`"
}

git_pull_merge_origin_main() {
  echo "..pull-merging latest remote main into current local [feature].."
  prompt_if_head_is_off_main
  exec_except_prompt git pull "$ORIGIN" "$MAIN"
}

git_pull_rebase_origin_main() {
  echo "..pull-rebasing current local [feature] onto latest remote main.."
  prompt_if_head_is_off_main
  exec_except_prompt git pull --rebase "$ORIGIN" "$MAIN"
}

confirm_setup() {
  prompt_until_yes "pulling from remote(s) to $LOCAL_REPO_PATH"
  prompt_until_yes "pulling repos ${REPO_NAMES[*]}"
}


$I_AM_LEET_HACKERMAN || confirm_setup

for REPO_NAME in ${REPO_NAMES[@]}; do
  # if current repo is in list of excluded repos, skip it
  SKIP=false
  for EXCL_REPO_NAME in ${EXCL_REPO_NAMES[@]}; do
    # if current repo is an excluded repo, set the flag,
    # then stop checking further exclusions (now we've ID'd it, no need to waste more time)
    [[ "$REPO_NAME" == "$EXCL_REPO_NAME" ]] && SKIP=true && break
  done
  # if the flag was set, skip this repo
  $SKIP && continue

  echo "next repo: $REPO_NAME.."
  exec_except_prompt cd "$LOCAL_REPO_PATH/$REPO_NAME"

  echo "..remote is at:"
  exec_except_prompt git remote -v
  echo "..local is at:"
  pwd
  echo "..local branches:"
  exec_except_prompt git branch

  echo "..status:"
  GIT_STATUS=$(git status)
  # d[elete] blank lines
  echo "$GIT_STATUS" | sed "/^$/d"
  # hacky.. git's "nothing to see here" status message is 4 lines long
  [[ $(echo "$GIT_STATUS" | wc -l) -ne 4 ]] && prompt_until_yes "..git status check failed"

  echo "..updating.."
  # [[ I_AM_LEET_HACKERMAN ]] && git_pull_rebase_origin_main || git_checkout_main_and_pull
  [[ I_AM_LEET_HACKERMAN ]] && git_pull_merge_origin_main || git_checkout_main_and_pull

  echo "..done!"
  echo  # blank line
done
