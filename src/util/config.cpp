#include <util/config.hpp>
#include <xml/rapidxml.hpp>
#include <xml/rapidxml_utils.hpp>
#include <util/erroradapters.hpp>

namespace util {

ConfigMgr* ConfigMgr::s_instance = NULL;

ConfigMgr::ConfigMgr()
{
}

ConfigMgr::~ConfigMgr()
{
}

void ConfigMgr::destroy()
{
	if (s_instance)
		delete s_instance;
}

void ConfigMgr::save(const std::string& path)
{
	using namespace rapidxml;

	// create document
	xml_document<> doc;

	// create XML declaration
	xml_node<>* declaration = doc.allocate_node(node_declaration);
	doc.append_node(declaration);
	declaration->append_attribute(doc.allocate_attribute("version", "1.0"));
    declaration->append_attribute(doc.allocate_attribute("encoding", "utf-8"));


	// create root element "config"
	xml_node<>* config = doc.allocate_node(node_element, "config");
	doc.append_node(config);

	xml_node<>* data;
	xml_attribute<>* key;
	char* pKey;
	xml_attribute<>* value;
	char* pValue;

	ConfigMgr::iterator it;
	for(it = this->begin(); it != this->end(); ++it) {
		data = doc.allocate_node(node_element, "data");
		config->append_node(data);

		pKey = doc.allocate_string(it->first.c_str());
		key = doc.allocate_attribute("key", pKey);
		data->append_attribute(key);

		pValue = doc.allocate_string(it->second.c_str());
		value = doc.allocate_attribute("value", pValue);
		data->append_attribute(value);
	}
}

void ConfigMgr::load(const std::string& fileName)
{
	using namespace rapidxml;

	/* information for error messages */
	std::string function = "ConfigMgr::load";
	std::vector<std::string> args;
	args.push_back(fileName);
	/* END information for error messages */

	using namespace rapidxml;

	char* m;
	file<char>* f = 0;

	std::string key;
	std::string value;

	try {
		f = new file<char>(fileName.c_str());
	} catch ( std::runtime_error& e ) {
		util::ErrorAdapter::instance().displayErrorMessage(function, args, e);
		if(f) delete f;
	} catch (...) {
		util::ErrorAdapter::instance().displayErrorMessage(function, args);
		if(f) delete f;
	}

	try {
		m = f->data();
		
		xml_document<> materials;
		materials.parse<0>(m);

		// this is important so we don't parse the config tag but the data tags
		xml_node<>* nodes = materials.first_node("config");
		if( nodes ) { 
			for (xml_node<>* node = nodes->first_node("data"); node; node = node->next_sibling("data")) {
				key = std::string(node->first_attribute("key")->value());
				value = std::string(node->first_attribute("value")->value());
				(*this)[key] = value;
			}
			delete f;
		} else {
			delete f;
			throw parse_error("No valid root node found", m);
		}
	} catch( parse_error& e ) {
		util::ErrorAdapter::instance().displayErrorMessage(function, args, e);
		delete f;
	} catch(...) {
		util::ErrorAdapter::instance().displayErrorMessage(function, args);
		delete f;
	}
}

std::string& ConfigMgr::getValue(const std::string& key)
{
	ConfigMgr::iterator it = (*this).begin();
	it = (*this).find(key);
	if(it != (*this).end())	
		return it->second;
	else 
		return std::string("");
}

void ConfigMgr::set(const std::string& key, const std::string& value)
{
	bool exists = false;
	ConfigMgr::iterator it = (*this).begin();
	it = (*this).find(key);
	if(it != (*this).end()) 
		exists = true;
	if(exists) 
		(*this)[key] = value;
	else 
		return;
}
}