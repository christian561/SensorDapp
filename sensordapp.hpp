#include <eosiolib/eosio.hpp>

using namespace eosio;

CONTRACT sensordapp : public contract {

public:
     sensordapp(name receiver, name code, datastream<const char*> ds) : contract(receiver, code, ds) { } 
 

	 TABLE sensor{
		 uint64_t id;
	     name owner;
		 std::string location;
		 std::vector<std::string> labels;
		
		 uint64_t primary_key() const { return id; }
	 };
	 
	typedef multi_index<"sensors"_n, sensor> sensors;
	 
 };

 private:
	TABLE userallowed{
	     name user;
	     uint64_t primary_key() const { return user.value; }
	 };
	 
	typedef multi_index<"whitelist"_n, userallowed> whitelist;
	 
};

/// @abi action
ACTION grantuser(const name& user);
/// @abi action
ACTION revokeuser(const name& user);
/// @abi action
ACTION newsensor(const name& owner, const uint64_t& id, const
	std::string& location, const std::vector<std::string>&labels);
/// @abi action
ACTION deletesensor(const name& owner, const uint64_t id);
/// @abi action
ACTION multiupload(const name& owner, const uint64_t& id,
	const uint64_t& timestamp, const std::vector<double>& values)