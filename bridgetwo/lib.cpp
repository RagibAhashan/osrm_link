#include <iostream>
#include "osrm/match_parameters.hpp"
#include "osrm/nearest_parameters.hpp"
#include "osrm/route_parameters.hpp"
#include "osrm/table_parameters.hpp"
#include "osrm/trip_parameters.hpp"
#include "engine/api/base_result.hpp"
#include "osrm/osrm_fwd.hpp"
#include "osrm/status.hpp"
#include <memory>
#include <string>
#include "osrm/coordinate.hpp"
#include "osrm/engine_config.hpp"
#include "osrm/json_container.hpp"

#include "engine/api/match_parameters.hpp"
#include "engine/api/nearest_parameters.hpp"
#include "engine/api/route_parameters.hpp"
#include "engine/api/table_parameters.hpp"
#include "engine/api/trip_parameters.hpp"

#include "engine/engine_config.hpp"
#include "engine/status.hpp"

#include "osrm/osrm.hpp"
#include "osrm/status.hpp"

#include <exception>
#include <iostream>
#include <string>
#include <utility>

#include <cstdlib>

#include "storage/storage_config.hpp"
#include <boost/filesystem/path.hpp>
#include <string>

using namespace osrm;

extern "C" {
    void test() { std::cout << "test\n"; }

    int match() {


        // Configure based on a .osrm base path, and no datasets in shared mem from osrm-datastore
        EngineConfig config;

        config.storage_config = {boost::filesystem::path("../maps/canada-latest.osrm")};
        config.use_shared_memory = false;

        // We support two routing speed up techniques:
        // - Contraction Hierarchies (CH): requires extract+contract pre-processing
        // - Multi-Level Dijkstra (MLD): requires extract+partition+customize pre-processing
        //
        // config.algorithm = EngineConfig::Algorithm::CH;
        config.algorithm = EngineConfig::Algorithm::MLD;

        // Routing machine with several services (such as Route, Table, Nearest, Trip, Match)
        const OSRM osrm{config};

        // // The following shows how to use the Route service; configure this service
        // RouteParameters params;

        // // Route in monaco
        // params.coordinates.push_back({util::FloatLongitude{7.419758}, util::FloatLatitude{43.731142}});
        // params.coordinates.push_back({util::FloatLongitude{7.419505}, util::FloatLatitude{43.736825}});

        // // Response is in JSON format
        // engine::api::ResultT result = json::Object();

        // // Execute routing request, this does the heavy lifting
        // const auto status = osrm.Route(params, result);
        std::string coordinates = "-73.630014,45.538450;-73.629229,45.538223;-73.628773,45.538102;-73.628473,45.538008;-73.628210,45.537922;-73.627926,45.537873";
        // Latitude,  Longitude,  Timestamp
        // 45.538450, -73.630014, 1660621345032
        // 45.538223, -73.629229, 1660621347061
        // 45.538102, -73.628773, 1660621349001
        // 45.538008, -73.628473, 1660621350824
        // 45.537922, -73.628210, 1660621352547
        // 45.537873, -73.627926, 1660621354346
        MatchParameters match_param;

        // util::Coordinate

        // std::vector<util::Coordinate> trip_coordinates;
        match_param.coordinates.push_back({util::FloatLongitude{-73.630014}, util::FloatLatitude{45.538450}});
        match_param.coordinates.push_back({util::FloatLongitude{-73.629229}, util::FloatLatitude{45.538223}});
        match_param.coordinates.push_back({util::FloatLongitude{-73.628773}, util::FloatLatitude{45.538102}});
        match_param.coordinates.push_back({util::FloatLongitude{-73.628473}, util::FloatLatitude{45.538008}});
        match_param.coordinates.push_back({util::FloatLongitude{-73.628210}, util::FloatLatitude{45.537922}});
        match_param.coordinates.push_back({util::FloatLongitude{-73.627926}, util::FloatLatitude{45.537873}});

        // std::vector<unsigned> match_timestamps;
        match_param.timestamps.push_back(1660621345032);
        match_param.timestamps.push_back(1660621347061);
        match_param.timestamps.push_back(1660621349001);
        match_param.timestamps.push_back(1660621350824);
        match_param.timestamps.push_back(1660621352547);
        match_param.timestamps.push_back(1660621354346);

        // match_param.coordinates = trip_coordinates;
        // match_param.timestamps = match_timestamps;
        



        engine::api::ResultT result;
        try
        {   
            const auto status = osrm.Match(match_param, result);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
        


        // auto &json_result = result.get<json::Object>();
        // if (status == Status::Ok)
        // {
        //     auto &routes = json_result.values["routes"].get<json::Array>();

        //     // Let's just use the first route
        //     auto &route = routes.values.at(0).get<json::Object>();
        //     const auto distance = route.values["distance"].get<json::Number>().value;
        //     const auto duration = route.values["duration"].get<json::Number>().value;

        //     // Warn users if extract does not contain the default coordinates from above
        //     if (distance == 0 || duration == 0)
        //     {
        //         std::cout << "Note: distance or duration is zero. ";
        //         std::cout << "You are probably doing a query outside of the OSM extract.\n\n";
        //     }

        //     std::cout << "Distance: " << distance << " meter\n";
        //     std::cout << "Duration: " << duration << " seconds\n";
        //     return EXIT_SUCCESS;
        // }
        // else if (status == Status::Error)
        // {
        //     const auto code = json_result.values["code"].get<json::String>().value;
        //     const auto message = json_result.values["message"].get<json::String>().value;

        //     std::cout << "Code: " << code << "\n";
        //     std::cout << "Message: " << code << "\n";
        //     return EXIT_FAILURE;
        // }

        return 1;
    }
}