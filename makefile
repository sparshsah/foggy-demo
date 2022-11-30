# author: sparshsah


# make, and thus makefiles, are all about MAKING FILES.
# The general format is to specify a target (file), dependent on some dependencies (files): e.g. "tgt.ext: dep1.ext dep2.ext".

# When you call `make tgt.ext`, make will first run `make dep1.ext`, then run `make dep2.ext`.
# The entire process is recursive, so if the target dep1.ext is specified as "dep1.ext: lowerdep1.ext",
# make will immediately run `make lowerdep1.ext` before executing the commands specified in `make dep1.ext`.
# The recursion terminates when either
# (a) make hits a target lowestdep.ext with no dependencies,
#     In which case it will check whether the file "lowestdep.ext" exists,
#     and if it doesn't, execute the commands specified in `make lowestdep.ext`
# or
# (b) make hits a "target" lowestdep_norecipe.ext with NO RECIPE, i.e.
#     there is no entry "lowestdep_norecipe.ext" in the makefile,
#     In which case make will confirm that "lowestdep_norecipe.ext" exists already...
#     and make doesn't know how to build it, so it had better exist!

# Now we go back to the top:
# By hook (make made them) or
# by crook (make didn't know how to make them, but fortunately they existed already),
# the files "dep1.ext" and "dep2.ext" exist now.
# make now checks whether the file "tgt.ext" is older than either "dep1.ext" or "dep2.ext".
# If it is older, make will execute the commands specified in `make tgt.ext`;
# else, it will inform you that tgt.ext is up-to-date, then do nothing.
# Of course, it's also possible that the file "tgt.ext" simply doesn't exist at all yet,
# in which case make will immediately execute the commands specified in `make tgt.ext`.

# The simplest case is when you directly run `make tgt.ext`,
# and tgt.ext doesn't specify any dependencies:
# In that case, make will check whether the file "tgt.ext" exists,
# and if it doesn't, execute the commands in the tgt.ext recipe.

# Now let's think about the canonical `make clean`, which idiomatically cleans up the directory.
# The goal is NOT to make a file called "clean": the goal is to clean up the directory!
# Now this is a bit cheating, since make will check whether the file "clean" exists,
# discover that it doesn't, then execute the commands specified in the recipe `make clean`.
# I call this a bit cheating because I already said make is all about making files...
# but the recipe `make clean` still doesn't actually end up creating a file called "clean".
# It's OK, but one consequence is that if you run `make clean` then immediately run `make clean` again,
# make will blindly execute the recipe both times.
# ... But wait... what if you DO happen to have a file called "clean" in the directory?
# make will check whether it exists, see that it does, inform you that it's up-to-date
# (after all, it has no dependencies, so as long as it exists it can never go out-of-date),
# then... do nothing!
# Therefore, when we specify recipes where the goal is not to make a file called "recipe",
# but rather to execute a set of commands, we list them as phony.
# If a recipe is phony, make will always execute it, regardless of whether a file of that name exists already.

.PHONY: nbconvert clean diff commit

nbconvert:
	# convert a jupyter notebook to a PDF via LaTeX
	# e.g. `make nbconvert f="path/to/nb"`,
	#     but do NOT include the ".ipynb" extension!
	jupyter nbconvert "$f.ipynb" --to="PDF"
	# rename it the way i like
	mv "$f.pdf" "$f.ipynb.pdf"

clean:
	# for Python projects
	# delete compiled bytecode
	find . -name "*.py[cod]" -exec rm {} +
	# Python 3 uses separate directory for compiled bytecode
	find . -name "__pycache__" -exec rm -r {} +
	find . -name ".ipynb_checkpoints" -exec rm -r {} +

diff:
	clear && git status && git diff

commit:
	# e.g. `make commit f="source.py" m="commit message"`
	# TODO(sparshsah): why can't i just do `f=${f:="."}` or
	#     `[[ -z "$f" ]] && f="."` for this line?
	echo "files = $f" && echo "commit message = $m"
	# catch merge conflicts
	git pull
	git add $f && git commit -m "$m" && git push && git status
