## Version 0.0

```

GalaxySim n-body simulation v0.0
Tue Oct  1 15:41:58 2019

Specifications:
	n = 1000
	image dimensions = 800x800
	frames = 500

Done.
Time used rendering images and saving them to file:
	44.340s total for 500 frames
	88.680ms on average

Time used updating the universe state:
	6.593s total for 500 frames
	13.187ms on average

```

Clearly, improving the rendering/saving efficiency would yield the greatest performance gain currently.

## Version 0.1

```
$ ./nbody 300 1000

GalaxySim n-body simulation v0.1
Tue Oct  1 16:42:17 2019

Specifications:
	n = 300
	image dimensions = 400x400
	frames = 1000

Done.

Time used rendering images and saving them to file:
	22.823s total for 1000 frames
	22.823ms on average

Time used updating the universe state:
	13.153s total for 1000 frames
	13.153ms on average

```

For now, we are generating small images to work around the overhead of saving to file.
