# ModulatedMedianFilter
A stereo median filter (see description) with an option to modulate the readout of circular buffer

"The median filter is a very interesting and somewhat strange algorithm. It has no IR or frequency response. It smoothes an input signal, which is an LPF type of operation, but it preserves transient edges, which is very un-LPF in nature. It has applications in noise reduction without losing high-frequency transients. Its central algorithm uses a sorting mechanism to sort the window of data by amplitude. The median value is chosen from the sort operation as the output. When the next sample arrives, the window is re-sorted and the next median value is obtained..." (Pirkle, Designing Audio Effect Plug-Ins in C++ With Digital Audio Signal Processing Theory, http://www.amazon.com/Designing-Audio-Effect-Plug-Ins-Processing/dp/0240825152/ref=sr_1_1?ie=UTF8&qid=1425531083&sr=8-1&keywords=pirkle)

The selection of the median point is performed with the selection algorithm (http://en.wikipedia.org/wiki/Selection_algorithm) with a k of half the size of the array.
