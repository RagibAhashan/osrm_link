#include <iostream>
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

#include "osrm/engine/api/match_parameters.hpp"

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
#include <osrm/json_container.hpp>
// #include <util/json_renderer.hpp>

using namespace osrm;
using namespace std;

// char* json_to_string(json::Object& result){
//     vector<char> out;
//     render(out, result);
//     string sout(out.begin(), out.end());
//     auto x = sout.c_str();
    // char* y = new char[out.size() + 1];
    // strcpy(y, x);
    // return y;
// }

extern "C" void osrm_free_char(char* str){
    delete[] str;
}


extern "C" {
    void test() { std::cout << "test\n"; }

    void* osrm_init() {
        EngineConfig config;
        config.use_shared_memory = false;
        config.algorithm = EngineConfig::Algorithm::MLD;
        config.storage_config = {boost::filesystem::path("../maps/canada-latest.osrm")};

        try
        {
            cout << "Starting OSRM engine...\n";

            OSRM* osrm = new OSRM(config);
            cout << "Engine started\n";
            return static_cast<void*>(osrm);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return static_cast<void*>(NULL);
        }
    }

    void osrm_delete(void* osrm_p) {
        OSRM* osrm = static_cast<OSRM*>(osrm_p);
        cout << "Deleting osrm ptr\n";
        delete osrm;
    }

    void osrm_match(
        void* osrm_ptr,
        int n,
        double* longitudes,
        double* latitudes,
        double* matched_long,
        double* matched_lat
    ) {

        MatchParameters match_param;

        for(int i=0; i < n; i++) {
            match_param.coordinates.push_back({
                util::FloatLongitude{longitudes[i]},
                util::FloatLatitude{latitudes[i]}
            });
        }

        engine::api::ResultT result = json::Object();
        try
        {  
            OSRM* osrm = static_cast<OSRM*>(osrm_ptr);
            const auto status = osrm->Match(match_param, result);
            auto &json_result = result.get<json::Object>();

            if (status == Status::Ok)
            {
                auto &routes = json_result.values["tracepoints"].get<json::Array>();

                for (int i = 0; i < json_result.values["tracepoints"].get<json::Array>().values.size(); i++)
                {
                    auto &route = routes.values.at(i).get<json::Object>();
                    auto &location = route.values["location"].get<json::Array>();
                    cout << location.values.at(0).get<json::Number>().value << " , "<<  location.values.at(1).get<json::Number>().value << endl;
                    matched_long[i] = location.values.at(0).get<json::Number>().value;
                    matched_lat[i] = location.values.at(1).get<json::Number>().value;
                }
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }


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


        std::string coordinates = "-73.630014,45.538450;-73.629229,45.538223;-73.628773,45.538102;-73.628473,45.538008;-73.628210,45.537922;-73.627926,45.537873";
        // Latitude,  Longitude,  Timestamp
        // 45.538450, -73.630014, 1660621345032
        // 45.538223, -73.629229, 1660621347061
        // 45.538102, -73.628773, 1660621349001
        // 45.538008, -73.628473, 1660621350824
        // 45.537922, -73.628210, 1660621352547
        // 45.537873, -73.627926, 1660621354346

        MatchParameters match_param;

        // std::vector<util::Coordinate> trip_coordinates;
        match_param.coordinates.push_back({util::FloatLongitude{-73.630014}, util::FloatLatitude{45.538450}});
        match_param.coordinates.push_back({util::FloatLongitude{-73.629229}, util::FloatLatitude{45.538223}});
        match_param.coordinates.push_back({util::FloatLongitude{-73.628773}, util::FloatLatitude{45.538102}});
        match_param.coordinates.push_back({util::FloatLongitude{-73.628473}, util::FloatLatitude{45.538008}});
        match_param.coordinates.push_back({util::FloatLongitude{-73.628210}, util::FloatLatitude{45.537922}});
        match_param.coordinates.push_back({util::FloatLongitude{-73.627926}, util::FloatLatitude{45.537873}});

        engine::api::ResultT result = json::Object();
        try
        {  
            // Status Match(const MatchParameters &parameters, engine::api::ResultT &result) const; 
            const auto status = osrm.Match(match_param, result);
            auto &json_result = result.get<json::Object>();



            if (status == Status::Ok)
            {
                auto &routes = json_result.values["tracepoints"].get<json::Array>();

                for (int i = 0; i < json_result.values["tracepoints"].get<json::Array>().values.size(); i++)
                {
                    auto &route = routes.values.at(i).get<json::Object>();
                    auto &location = route.values["location"].get<json::Array>();
                    cout << location.values.at(0).get<json::Number>().value << " , "<<  location.values.at(1).get<json::Number>().value << endl;

                }
                return 1;
            }
            
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        return 1;
    }
}