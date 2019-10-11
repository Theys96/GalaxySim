In this experiment we measure the discrepancies in the total energy of our simulation's energy at the beginning of the simulation and after a specific number of time steps T (`nframes` in the program).  
For all runs, the `dt` value is equal, that is the 'size' of each time step (here, `dt` is always 0.02).
We make measurements for our 3 current main iteration methods: Euler, Barnes-Hut and Most-Significant-Bodies.
The number of bodies (N = 200) is relatively low to speed up the computation, but equal for every run.
Note that a custom main function was used for this experiment, with custom output. Every output represents 20 runs of a simulation.

```
$ ./energy.sh

GalaxySim n-body simulation v1.2.3
Fri Oct 11 15:20:41 2019
CUSTOM program for measuring energy discrepancies.

dt = 0.02
method = Euler
n (bodies) = 200
nframes = 100

+0.151%
-0.121%
-0.333%
+0.013%
-0.175%
-0.301%
-0.252%
-0.337%
-0.262%
-0.173%
-0.195%
-0.247%
-0.226%
-0.215%
-0.095%
-0.272%
+0.102%
-0.058%
-0.308%
-0.323%

GalaxySim n-body simulation v1.2.3
Fri Oct 11 15:20:42 2019
CUSTOM program for measuring energy discrepancies.

dt = 0.02
method = Euler
n (bodies) = 200
nframes = 200

-0.122%
-0.439%
-0.884%
-0.358%
-0.253%
-0.385%
-0.336%
-0.254%
-0.256%
-0.498%
-0.494%
-0.297%
-0.172%
-0.388%
-0.389%
-0.424%
-0.005%
-0.339%
-0.334%
-0.411%

GalaxySim n-body simulation v1.2.3
Fri Oct 11 15:20:44 2019
CUSTOM program for measuring energy discrepancies.

dt = 0.02
method = Euler
n (bodies) = 200
nframes = 500

-0.343%
-0.453%
-0.486%
-0.356%
-0.135%
-0.210%
-0.972%
-0.335%
-0.528%
-0.177%
+0.348%
+0.018%
-0.347%
-0.737%
+0.024%
-0.483%
-0.340%
-0.343%
-0.700%
-0.133%

GalaxySim n-body simulation v1.2.3
Fri Oct 11 15:20:50 2019
CUSTOM program for measuring energy discrepancies.

dt = 0.02
method = Euler
n (bodies) = 200
nframes = 1000

-0.765%
-0.338%
-0.683%
-0.199%
-1.210%
-0.616%
+0.057%
-0.394%
-0.725%
-1.284%
-0.055%
-0.829%
-0.847%
-0.622%
-0.416%
-0.457%
-0.498%
-0.816%
+0.035%
-0.759%

GalaxySim n-body simulation v1.2.3
Fri Oct 11 15:21:00 2019
CUSTOM program for measuring energy discrepancies.

dt = 0.02
method = Euler
n (bodies) = 200
nframes = 1500

-0.556%
-0.269%
-0.744%
-0.183%
-0.697%
-0.595%
-0.539%
-1.598%
-0.691%
+0.231%
-0.147%
-0.686%
-0.449%
-0.468%
-0.884%
-0.745%
-0.332%
-0.556%
-0.649%
-1.028%

GalaxySim n-body simulation v1.2.3
Fri Oct 11 15:21:16 2019
CUSTOM program for measuring energy discrepancies.

dt = 0.02
method = Euler
n (bodies) = 200
nframes = 2000

-0.179%
-0.301%
+0.027%
-0.685%
-0.215%
-1.065%
-0.809%
-0.428%
+0.803%
-0.287%
-1.121%
+0.617%
-1.119%
-0.492%
-0.815%
-1.070%
-1.428%
-1.617%
-0.754%
-0.684%

GalaxySim n-body simulation v1.2.3
Fri Oct 11 15:21:36 2019
CUSTOM program for measuring energy discrepancies.

dt = 0.02
method = Euler
n (bodies) = 200
nframes = 3000

+0.065%
-0.778%
-0.723%
-1.115%
-1.229%
-1.131%
-0.630%
-1.343%
-0.061%
-0.428%
+0.369%
-1.113%
-0.809%
-0.679%
-0.473%
-1.154%
-0.659%
-0.473%
-0.446%
-0.710%

GalaxySim n-body simulation v1.2.3
Fri Oct 11 15:22:07 2019
CUSTOM program for measuring energy discrepancies.

dt = 0.02
method = Euler
n (bodies) = 200
nframes = 5000

+0.192%
-1.257%
+0.177%
-0.339%
-0.935%
-0.482%
-1.604%
-1.794%
-1.406%
-0.869%
+0.192%
-0.226%
-1.032%
+0.344%
+1.393%
-1.553%
-2.039%
-1.719%
-1.117%
-0.593%

GalaxySim n-body simulation v1.2.3
Fri Oct 11 15:22:57 2019
CUSTOM program for measuring energy discrepancies.

dt = 0.02
method = Barnes-Hut
n (bodies) = 200
nframes = 100

-0.146%
-0.040%
-0.179%
-0.197%
-0.044%
-0.290%
-0.337%
-0.232%
-0.203%
-0.222%
-0.350%
-0.520%
-0.197%
-0.164%
-0.401%
-0.120%
-0.238%
-0.258%
-0.345%
-0.082%

GalaxySim n-body simulation v1.2.3
Fri Oct 11 15:23:00 2019
CUSTOM program for measuring energy discrepancies.

dt = 0.02
method = Barnes-Hut
n (bodies) = 200
nframes = 200

-0.434%
-0.563%
-0.531%
-0.015%
-0.466%
-0.633%
-0.060%
-0.177%
-0.275%
-0.943%
-0.362%
-0.475%
-0.631%
-0.439%
-0.536%
-0.465%
-0.281%
-0.171%
-0.298%
-0.314%

GalaxySim n-body simulation v1.2.3
Fri Oct 11 15:23:06 2019
CUSTOM program for measuring energy discrepancies.

dt = 0.02
method = Barnes-Hut
n (bodies) = 200
nframes = 500

-0.715%
-0.334%
-0.433%
-1.104%
-1.121%
-1.065%
-0.754%
-1.446%
-0.318%
-0.540%
-0.441%
-0.878%
-0.677%
-0.401%
-0.432%
-0.524%
-0.617%
-0.534%
-0.242%
-0.139%

GalaxySim n-body simulation v1.2.3
Fri Oct 11 15:23:19 2019
CUSTOM program for measuring energy discrepancies.

dt = 0.02
method = Barnes-Hut
n (bodies) = 200
nframes = 1000

-1.290%
-1.067%
-0.829%
-1.278%
-0.770%
-1.072%
-0.725%
-0.642%
-0.758%
-1.529%
-1.105%
-0.683%
-1.195%
-0.641%
-1.094%
-1.234%
-0.673%
-0.912%
-1.948%
-1.188%

GalaxySim n-body simulation v1.2.3
Fri Oct 11 15:23:45 2019
CUSTOM program for measuring energy discrepancies.

dt = 0.02
method = Barnes-Hut
n (bodies) = 200
nframes = 1500

-0.544%
-2.122%
-0.110%
-2.025%
-1.895%
-0.903%
-1.688%
-1.058%
+0.280%
-1.816%
+0.233%
+0.244%
-1.027%
-0.925%
+0.106%
-1.149%
+0.313%
-1.222%
-0.358%
-1.643%

GalaxySim n-body simulation v1.2.3
Fri Oct 11 15:24:24 2019
CUSTOM program for measuring energy discrepancies.

dt = 0.02
method = Barnes-Hut
n (bodies) = 200
nframes = 2000

-0.536%
-1.124%
-2.828%
-0.280%
+0.173%
+0.287%
-0.896%
+0.051%
-1.047%
-4.601%
-0.957%
-0.448%
-1.345%
-0.613%
-2.501%
-0.023%
-1.248%
-0.993%
-0.578%
+1.214%

GalaxySim n-body simulation v1.2.3
Fri Oct 11 15:25:16 2019
CUSTOM program for measuring energy discrepancies.

dt = 0.02
method = Barnes-Hut
n (bodies) = 200
nframes = 3000

-1.867%
-0.351%
-1.358%
-9.925%
-0.790%
-0.901%
-0.953%
-1.485%
-0.599%
-3.332%
+1.874%
-2.643%
-7.634%
-3.896%
+0.032%
-4.007%
-1.088%
-1.286%
-3.005%
-0.299%

GalaxySim n-body simulation v1.2.3
Fri Oct 11 15:26:33 2019
CUSTOM program for measuring energy discrepancies.

dt = 0.02
method = Barnes-Hut
n (bodies) = 200
nframes = 5000

-6.385%
-0.898%
+1.450%
-9.409%
-13.892%
-1.069%
-1.673%
-0.371%
-2.653%
-3.352%
+0.815%
-3.239%
-3.559%
-2.516%
-4.225%
-2.307%
-3.948%
-3.510%
-5.344%
-6.984%

GalaxySim n-body simulation v1.2.3
Fri Oct 11 15:28:41 2019
CUSTOM program for measuring energy discrepancies.

dt = 0.02
method = Most-Significant
n (bodies) = 200
nframes = 100

-0.188%
-0.351%
-0.067%
-0.067%
-0.170%
-0.344%
-0.344%
-0.166%
-0.380%
-0.380%
-0.120%
-0.185%
-0.185%
-0.112%
-0.152%
-0.152%
-0.305%
-0.308%
-0.191%
-0.191%

GalaxySim n-body simulation v1.2.3
Fri Oct 11 15:28:41 2019
CUSTOM program for measuring energy discrepancies.

dt = 0.02
method = Most-Significant
n (bodies) = 200
nframes = 200

-0.516%
-0.345%
-0.212%
-0.126%
-0.598%
-0.460%
-0.351%
-0.323%
-0.360%
-0.180%
-0.566%
-0.328%
-0.494%
-0.281%
-0.308%
-0.599%
-0.478%
-0.236%
-0.334%
-0.430%

GalaxySim n-body simulation v1.2.3
Fri Oct 11 15:28:41 2019
CUSTOM program for measuring energy discrepancies.

dt = 0.02
method = Most-Significant
n (bodies) = 200
nframes = 500

-0.492%
-0.548%
-0.613%
-0.708%
-0.659%
-0.503%
-0.554%
-0.756%
-0.592%
-0.420%
-0.674%
-0.520%
-0.493%
-0.511%
-0.741%
-0.302%
-0.394%
-0.467%
-0.708%
-0.595%

GalaxySim n-body simulation v1.2.3
Fri Oct 11 15:28:41 2019
CUSTOM program for measuring energy discrepancies.

dt = 0.02
method = Most-Significant
n (bodies) = 200
nframes = 1000

-0.782%
-0.777%
-0.556%
-0.546%
-0.765%
-0.714%
-0.563%
-0.672%
-0.790%
-0.579%
-0.617%
-0.522%
-0.749%
-0.681%
-0.825%
-0.353%
-0.575%
-0.660%
-0.635%
-0.653%

GalaxySim n-body simulation v1.2.3
Fri Oct 11 15:28:41 2019
CUSTOM program for measuring energy discrepancies.

dt = 0.02
method = Most-Significant
n (bodies) = 200
nframes = 1500

-0.512%
-0.529%
-0.476%
-0.408%
-0.590%
-0.679%
-0.601%
-0.489%
-0.561%
-0.650%
-0.677%
-0.704%
-0.614%
-0.355%
-0.484%
-0.599%
-0.403%
-0.505%
-0.671%
-0.778%

GalaxySim n-body simulation v1.2.3
Fri Oct 11 15:28:41 2019
CUSTOM program for measuring energy discrepancies.

dt = 0.02
method = Most-Significant
n (bodies) = 200
nframes = 2000

-0.335%
-0.457%
-0.455%
-0.621%
-0.640%
-0.415%
-0.464%
-0.506%
-0.564%
-0.437%
-0.502%
-0.180%
-0.255%
-0.512%
-0.308%
-0.510%
-0.429%
-0.670%
-0.542%
-0.585%

GalaxySim n-body simulation v1.2.3
Fri Oct 11 15:28:42 2019
CUSTOM program for measuring energy discrepancies.

dt = 0.02
method = Most-Significant
n (bodies) = 200
nframes = 3000

-0.375%
-0.727%
-0.491%
-0.371%
-0.430%
-0.053%
-0.511%
-0.611%
-0.483%
-0.468%
-0.541%
-0.374%
-0.539%
-0.496%
-0.533%
-0.473%
-0.519%
-0.267%
-0.490%
-0.385%

GalaxySim n-body simulation v1.2.3
Fri Oct 11 15:28:42 2019
CUSTOM program for measuring energy discrepancies.

dt = 0.02
method = Most-Significant
n (bodies) = 200
nframes = 5000

-0.430%
-0.461%
-0.715%
-0.778%
-0.541%
-0.548%
-0.486%
-0.669%
-0.513%
-0.645%
-0.365%
-0.565%
-0.432%
-0.754%
-0.724%
-0.525%
-0.427%
-0.495%
-0.637%
-0.618%
```