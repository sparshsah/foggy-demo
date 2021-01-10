# interactive demos

Note: For the sake of more conveniently viewing these demos,
we preserve the output. However, in general,
it's best practice to clear cell output
(particularly images) before checking into Git lest each "blob"
binary large object, referring to the encoding of each image's
pixels as a raw byte sequence) blow up the diffs.
With output cleared, a notebook is just plaintext/JSON.
(An image blob tends to be big to begin with,
and even visually minor edits like changing the size/color of an image,
or moving a couple elements around within it,
can dramatically change the blob, requiring Git to "remember" a
totally new version of the entire blob every time.
For illustration, the 6 images in
https://github.com/sparshsah/foggy-ml/blob/main/_demo/fann/demo_fann.ipynb
make that single file alone so big that GitHub labels the whole
repo as 99% Jupyter notebook files.)
