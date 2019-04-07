#include "sensordapp.hpp"
#include <eosiolib/eosio.hpp>

using namespace eosio;

ACTION sensordapp::grantuser(const name& user) {
	
		
		
}

ACTION sensordapp::revokeuser(const name& user) {
	
		
		
}

ACTION sensordapp::newsensor(const name& owner,
	const uint64_t& id, const std::string& location,
	const std::vector<std::string>& labels) {
	
		
		
}

 ACTION sensordapp::deletesensor(const name& owner,
	const uint64_t id) {
	
		
		
}

 ACTION sensordapp::multiupload(const name& owner,
	const uint64_t& id, const uint64_t& timestamp,
	const std::vector<double>& values) {
	
		
		
}
 
ACTION sensordapp::grantuser(const name& user) {
	    require_auth(_self);
	    whitelist existing_whitelist(_code, _code.value);
	    auto itr = existing_whitelist.find(user.value);
	    eosio_assert(itr == existing_whitelist.end(),
		 "User already exists");
	 
		    existing_whitelist.emplace(_self, [&](auto& w) {
		       w.user = user;
		    });
	 
 }

void sensordapp::revokeuser(const name& user) {
	   require_auth(_self);
	   whitelist existing_whitelist(_code, _code.value);
	   auto itr = existing_whitelist.find(user.value);
	   eosio_assert(itr != existing_whitelist.end(),
		"User does not exist");
	
		   existing_whitelist.erase(itr);
	
}

void sensordapp::newsensor(const name& owner,
	const uint64_t& id, const std::string& location,
	const std::vector<std::string>& labels) {
	    require_auth(owner);
	    eosio_assert(labels.size() < 10, "Too many labels");
	
		    whitelist existing_whitelist(_code, _code.value);
	    auto itr1 = existing_whitelist.find(owner.value);
	    eosio_assert(itr1 != existing_whitelist.end(),
		"User not allowed");
	
		    sensors existing_sensors(_code, owner.value);
	   auto itr2 = existing_sensors.find(id);
	   eosio_assert(itr2 == existing_sensors.end(),
		"Sensor already exists");
	
		   existing_sensors.emplace(owner, [&](auto& s) {
		      s.owner = owner;
		      s.id = id;
		      s.location = location;
		      s.labels = labels;
		   });
	
}

void sensordapp::deletesensor(const name& owner,
	const uint64_t id) {
	    require_auth(owner);
	
		    sensors existing_sensors(_code, owner.value);
	    auto itr = existing_sensors.find(id);
	    eosio_assert(itr != existing_sensors.end(),
		"Sensor does not exist");
	
		   existing_sensors.erase(itr);
	
}

void sensordapp::multiupload(const name& owner,
	const uint64_t& id, const uint64_t& timestamp,
	const std::vector<double>& values) {
	    require_auth(owner);
	
		    eosio_assert(values.size() < 10, "Too many sensor values");
	
		    whitelist existing_whitelist(_code, _code.value);
	    auto itr1 = existing_whitelist.find(owner.value);
	    eosio_assert(itr1 != existing_whitelist.end(),
		"User not allowed");
	
		    sensors existing_sensors(_code, owner.value);
	    auto itr2 = existing_sensors.find(id);
	    eosio_assert(itr2 != existing_sensors.end(),
		"Sensor does not exist");
	
		    eosio_assert(itr2->labels.size() == values.size(),
			"Values/Labels array size mismatch");
	
}

EOSIO_DISPATCH(sensordapp, (grantuser)(revokeuser)(newsensor)(deletesensor)(multiupload))