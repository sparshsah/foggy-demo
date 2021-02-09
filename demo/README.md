# interactive demos

Note: For the sake of more conveniently viewing these demos,
we preserve the output. However, in general,
it's best practice to clear cell output
(particularly images), turning the notebook into plaintext/JSON,
before checking into Git, lest each "blob"
(binary large object, referring to the encoding of each image's
pixels as a raw byte sequence) blow up the diffs.
(An image blob tends to be big to begin with,
as illustrated by the fact that the three histograms in
https://github.com/sparshsah/foggy-demo/blob/main/_demo/stats/expon-rv_univ-of-unif.ipynb
singlehandedly cause GitHub to label this whole repo as 95% Jupyter code.
Furthermore, even visually minor edits like changing the size/color of an image,
or moving a couple elements around within it,
can dramatically change the blob, requiring Git to "remember" a
totally new version of the entire blob every time.)
