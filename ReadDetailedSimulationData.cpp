// Interface from Falaise
#include "falaise/snemo/processing/module.h"

// Any data models we need
#include <bayeux/mctools/simulated_data.h>

class ReadDetailedSimulationData {
public:
  ReadDetailedSimulationData() = default;

  ReadDetailedSimulationData(falaise::config::property_set const & /*unused*/,
                             datatools::service_manager & /*unused*/) {}

  // Process event
  // This can be copied verbatim into the process method of a
  // pre Falaise 4 module
  falaise::processing::status process(datatools::things &event) {
    // Print most basic information about the event
    std::cout << "ReadDetailedSimulationData::process called!" << std::endl;
    std::cout << "- name        : " << event.get_name() << std::endl;
    std::cout << "- description : " << event.get_description() << std::endl;

    // Read simulated data bank
    auto &simData = event.get<mctools::simulated_data>("SD");

    // Read and print core hit collections, if any
    // See: https://supernemo.org/Falaise/usingflsimulate.html ("Available MC
    // hits output profiles")
    std::cout << "- Processed Steps:" << std::endl;

    for (const std::string &hitCollectionID : {"gg", "calo", "xcalo", "gveto"}) {
      if (simData.has_step_hits(hitCollectionID)) {
        const auto &hc = simData.get_step_hits(hitCollectionID);

        std::cout << "  + " << hitCollectionID << ", size = " << hc.size()
                  << std::endl;

        for (const datatools::handle<mctools::base_step_hit> &hit : hc) {
          std::cout << "    + " << hitCollectionID << " Step "
                    << hit->get_hit_id() << std::endl;
          ;

          hit->tree_dump(std::cout, "", "    ");
          // or do with the hit as you like

          break; // So only print first hit, remove for full output
        }
      }
    }

    // Read and print raw steps, if any
    // See: https://supernemo.org/Falaise/usingflsimulate.html ("Available MC
    // hits output profiles")
    std::cout << "- Raw Steps:" << std::endl;

    if (simData.has_step_hits("__visu.tracks")) {
      const auto &rawSteps = simData.get_step_hits("__visu.tracks");

      for (const datatools::handle<mctools::base_step_hit> &hit : rawSteps) {
        hit->tree_dump(std::cout, "+ Next Step:", "  ");

        break; // so only print first hit, remove for full output
      }
    }

    return falaise::processing::status::PROCESS_OK;
  }
};

FALAISE_REGISTER_MODULE(ReadDetailedSimulationData)
