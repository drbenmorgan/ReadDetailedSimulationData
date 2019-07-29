ReadDetailedSimulationData
==========================

Example Falaise module to read and print the full Geant4 steps from
a simulation output file, assuming they are available.

The module may be built and run like any other Falaise module,
see [the main documentation](https://supernemo.org/Falaise/writingflreconstructmodules.html)
for details.

Two scripts are supplied to run `flsimulate` and `flreconstruct`:

- ReadDetailedSimulationDataPipeline.conf
  - Example pipeline script for `flreconstruct`
- FlSimulateWithDetail.conf
  - Shows the needed variant setting to enable output of complete
    Geant4 steps.

The module itself simply iterates over the hit collections and dumps
their output to `std::cout`. These can be used as a starting point to
read more detailed information from the `mctools::base_step_hit` objects.
See https://supernemo.org/Bayeux/classmctools_1_1base__step__hit.html
for the interfaces offered by this class.

For additional information on the simulation output, see:

- https://supernemo.org/Falaise/usingflsimulate.html
- https://supernemo.org/Falaise/flsimulateoutput.html

