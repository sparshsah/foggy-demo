#!/bin/bash

LOCAL_REPO_PATH="/code/$(id -u -n)/"  # e.g. "/code/sparshsah/"
REPO_NAMES=$(ls $LOCAL_REPO_PATH | grep /)


prompt_until_yes() {
  echo "$1, ok? ('y' to continue/skip, 'Ctrl+C' to quit)"
  CONFIRM_INPUT="n"
  while [[ "$CONFIRM_INPUT" != "y" ]]; do
    read CONFIRM_INPUT
  done
}

exec_except_prompt() {
  $@ || prompt_until_yes "..error executing '$*' (exit status code $?, recommend quitting to debug)"
}

git_checkout_main() {
  # market leader GitHub has switched its default branch name, but not all devs have accepted
  git checkout main || git checkout master
}


prompt_until_yes "pulling from remote(s) to $LOCAL_REPO_PATH"
prompt_until_yes "pulling repos ${REPO_NAMES[*]}"

for REPO_NAME in ${REPO_NAMES[@]}; do
  # skip this repo
  [[ $REPO_NAME == "some-legacy-library/" ]] && continue

  echo "next repo: $REPO_NAME.."
  exec_except_prompt cd $LOCAL_REPO_PATH/$REPO_NAME

  echo "..local is at:"
  pwd
  echo "..remote is at:"
  exec_except_prompt git remote -v
  echo "..local branches:"
  exec_except_prompt git branch

  echo "..status:"
  GIT_STATUS=$(git status)
  echo "$GIT_STATUS" | sed "/^$/d"
  # hacky.. git's "nothing to see here" status message is 4 lines long
  [[ $(echo "$GIT_STATUS" | wc -l) -ne 4 ]] && prompt_until_yes "..git status check failed"

  echo "..switching to main and pulling.."
  # TODO(sparshsah): why can't i just use `(checkout && pull)` or `{ checkout && pull; }`?
  exec_except_prompt git_checkout_main
  exec_except_prompt git pull

  echo
done
