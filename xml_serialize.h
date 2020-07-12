//==============================================================================================================
//
// Project Name:
// XML  SERIALIZER
//           ------ wapper module of TINYXML2
//
// Motivation:
// This object serializer is the final project of OOP course
// taught by Xiang Chen, ZJU, 2020
//
// Function:
// This object serializer enable transformation between
// valid type of variable <----> XML file <----> base64 file
//
// Support types:
// 1-std::is_arithmetic
// 2-std::string + its nested type
// 3-std::map,std::list,std::vector,std::set,std::pair, + their nested type + their combined type
// 4-std::shared_ptr,std::unique_ptr
// 5-user defined struct with members less than 30 + its nested type + its combined type
//
// Main Idea:
// Use template and enable_if function to automatically recursively do serialization/ deserialization work
// When it comes to user defined type struct,
// get / put the variable of sub members in the struct and recursiely do serialization/ deserialization work
//
//
// Usage:
// All functions are packed in the namespace xml_serialize
//
// Author: Haofei YU
// Time  : 2020/07/12
//=============================================================================================================



#ifndef __XML_SERIALIZE_HPP__
#define __XML_SERIALIZE_HPP__

#include <iostream>
#include <strstream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <tuple>
#include <set>
#include <array>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <type_traits>
#include <functional>
#include <string_view>
#include <memory>
#include <utility>
#include "tinyxml2.h"


//=================================================
//
// marco
// used to do reflection
// struct we support is less than 30 parameters
// users need to define REFLECTION marco after declear struct
//
//=================================================


// reflection marco
#define REFLECTION(STRUCT_NAME, ...) \
MAKE_META_DATA(STRUCT_NAME, GET_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)

// core function
// use marco to create a function
// return a struct of tuple and provide several functions to help use the tuple
#define MAKE_META_DATA_IMPL(STRUCT_NAME, ...) \
static auto get_reflect_members(STRUCT_NAME const&) \
{ \
struct reflect_members \
{ \
constexpr decltype(auto) static apply_impl(){\
return std::make_tuple(__VA_ARGS__);\
}\
using type = void;\
using size_type = std::integral_constant<size_t, GET_ARG_COUNT(__VA_ARGS__)>; \
constexpr static std::string_view name() { return std::string_view(#STRUCT_NAME, sizeof(#STRUCT_NAME)-1); }\
constexpr static size_t value() { return size_type::value; }\
constexpr static std::array<std::string_view, size_type::value> arr() { return arr_##STRUCT_NAME; }\
}; \
return reflect_members{}; \
}


// used to analysis the number of __VA_ARGS__
// at most support 30 members in the user-defined struct
#define MAKE_META_DATA(STRUCT_NAME, N, ...) \
constexpr inline std::array<std::string_view, N> arr_##STRUCT_NAME = { MARCO_EXPAND(MACRO_CONCAT(CON_STR, N)(__VA_ARGS__)) };\
MAKE_META_DATA_IMPL(STRUCT_NAME, MAKE_ARG_LIST(N, &STRUCT_NAME::FIELD, __VA_ARGS__))

#define RSEQ_N() \
30,29,28,27,26,25,24,23,22,21,20, \
19,18,17,16,15,14,13,12,11,10, \
9,8,7,6,5,4,3,2,1,0

#define ARG_N(\
_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, \
_11, _12, _13, _14, _15, _16, _17, _18, _19, _20, \
_21, _22, _23, _24, _25, _26, _27, _28, _29, _30, \
N, ...) N

#define MARCO_EXPAND(...)                 __VA_ARGS__

#define FIELD(t)                          t

//note use MACRO_CONCAT like A##_##B direct may cause marco expand error
#define MACRO_CONCAT(A, B) MACRO_CONCAT1(A, B)
#define MACRO_CONCAT1(A, B) A##_##B

#define MAKE_ARG_LIST(N, op, arg, ...) \
MACRO_CONCAT(MAKE_ARG_LIST, N)(op, arg, __VA_ARGS__)

#define GET_ARG_COUNT_INNER(...)    MARCO_EXPAND(ARG_N(__VA_ARGS__))
#define GET_ARG_COUNT(...)          GET_ARG_COUNT_INNER(__VA_ARGS__, RSEQ_N())



#define MAKE_ARG_LIST_1(op, arg, ...)   op(arg)
#define MAKE_ARG_LIST_2(op, arg, ...)   op(arg), MARCO_EXPAND(MAKE_ARG_LIST_1(op, __VA_ARGS__))
#define MAKE_ARG_LIST_3(op, arg, ...)   op(arg), MARCO_EXPAND(MAKE_ARG_LIST_2(op, __VA_ARGS__))
#define MAKE_ARG_LIST_4(op, arg, ...)   op(arg), MARCO_EXPAND(MAKE_ARG_LIST_3(op, __VA_ARGS__))
#define MAKE_ARG_LIST_5(op, arg, ...)   op(arg), MARCO_EXPAND(MAKE_ARG_LIST_4(op, __VA_ARGS__))
#define MAKE_ARG_LIST_6(op, arg, ...)   op(arg), MARCO_EXPAND(MAKE_ARG_LIST_5(op, __VA_ARGS__))
#define MAKE_ARG_LIST_7(op, arg, ...)   op(arg), MARCO_EXPAND(MAKE_ARG_LIST_6(op, __VA_ARGS__))
#define MAKE_ARG_LIST_8(op, arg, ...)   op(arg), MARCO_EXPAND(MAKE_ARG_LIST_7(op, __VA_ARGS__))
#define MAKE_ARG_LIST_9(op, arg, ...)   op(arg), MARCO_EXPAND(MAKE_ARG_LIST_8(op, __VA_ARGS__))
#define MAKE_ARG_LIST_10(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_9(op, __VA_ARGS__))
#define MAKE_ARG_LIST_11(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_10(op, __VA_ARGS__))
#define MAKE_ARG_LIST_12(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_11(op, __VA_ARGS__))
#define MAKE_ARG_LIST_13(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_12(op, __VA_ARGS__))
#define MAKE_ARG_LIST_14(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_13(op, __VA_ARGS__))
#define MAKE_ARG_LIST_15(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_14(op, __VA_ARGS__))
#define MAKE_ARG_LIST_16(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_15(op, __VA_ARGS__))
#define MAKE_ARG_LIST_17(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_16(op, __VA_ARGS__))
#define MAKE_ARG_LIST_18(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_17(op, __VA_ARGS__))
#define MAKE_ARG_LIST_19(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_18(op, __VA_ARGS__))
#define MAKE_ARG_LIST_20(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_19(op, __VA_ARGS__))
#define MAKE_ARG_LIST_21(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_20(op, __VA_ARGS__))
#define MAKE_ARG_LIST_22(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_21(op, __VA_ARGS__))
#define MAKE_ARG_LIST_23(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_22(op, __VA_ARGS__))
#define MAKE_ARG_LIST_24(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_23(op, __VA_ARGS__))
#define MAKE_ARG_LIST_25(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_24(op, __VA_ARGS__))
#define MAKE_ARG_LIST_26(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_25(op, __VA_ARGS__))
#define MAKE_ARG_LIST_27(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_26(op, __VA_ARGS__))
#define MAKE_ARG_LIST_28(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_27(op, __VA_ARGS__))
#define MAKE_ARG_LIST_29(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_28(op, __VA_ARGS__))
#define MAKE_ARG_LIST_30(op, arg, ...)  op(arg), MARCO_EXPAND(MAKE_ARG_LIST_29(op, __VA_ARGS__))

#define ADD_VIEW(str) std::string_view(#str, sizeof(#str)-1)

#define SEPERATOR ,
#define CON_STR_1(element, ...) ADD_VIEW(element)
#define CON_STR_2(element, ...) ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_1(__VA_ARGS__))
#define CON_STR_3(element, ...) ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_2(__VA_ARGS__))
#define CON_STR_4(element, ...) ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_3(__VA_ARGS__))
#define CON_STR_5(element, ...) ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_4(__VA_ARGS__))
#define CON_STR_6(element, ...) ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_5(__VA_ARGS__))
#define CON_STR_7(element, ...) ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_6(__VA_ARGS__))
#define CON_STR_8(element, ...) ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_7(__VA_ARGS__))
#define CON_STR_9(element, ...) ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_8(__VA_ARGS__))
#define CON_STR_10(element, ...) ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_9(__VA_ARGS__))
#define CON_STR_11(element, ...) ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_10(__VA_ARGS__))
#define CON_STR_12(element, ...) ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_11(__VA_ARGS__))
#define CON_STR_13(element, ...) ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_12(__VA_ARGS__))
#define CON_STR_14(element, ...) ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_13(__VA_ARGS__))
#define CON_STR_15(element, ...) ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_14(__VA_ARGS__))
#define CON_STR_16(element, ...) ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_15(__VA_ARGS__))
#define CON_STR_17(element, ...) ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_16(__VA_ARGS__))
#define CON_STR_18(element, ...) ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_17(__VA_ARGS__))
#define CON_STR_19(element, ...) ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_18(__VA_ARGS__))
#define CON_STR_20(element, ...) ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_19(__VA_ARGS__))
#define CON_STR_21(element, ...) ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_20(__VA_ARGS__))
#define CON_STR_22(element, ...) ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_21(__VA_ARGS__))
#define CON_STR_23(element, ...) ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_22(__VA_ARGS__))
#define CON_STR_24(element, ...) ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_23(__VA_ARGS__))
#define CON_STR_25(element, ...) ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_24(__VA_ARGS__))
#define CON_STR_26(element, ...) ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_25(__VA_ARGS__))
#define CON_STR_27(element, ...) ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_26(__VA_ARGS__))
#define CON_STR_28(element, ...) ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_27(__VA_ARGS__))
#define CON_STR_29(element, ...) ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_28(__VA_ARGS__))
#define CON_STR_30(element, ...) ADD_VIEW(element) SEPERATOR MARCO_EXPAND(CON_STR_29(__VA_ARGS__))






namespace xml_serialize {
	using namespace std;
	using namespace tinyxml2;

	//=================================================
	//
	// function declearation
	// include both declearation and definition to solve the problem of overload
	//
	//=================================================

	// shared function
	void create_XML(const char* XML_path);
	// base type
	template<typename T> typename std::enable_if<std::is_arithmetic<T>::value, void>::type serialize_xml(T & object, const char * object_typename, const char * XML_path);
	template<typename T> typename std::enable_if<std::is_arithmetic<T>::value, void>::type serialize_xml(T & object, const char * object_typename, const char * XML_path, XMLDocument * ptr_doc, XMLElement * root);
	template<typename T> typename std::enable_if<std::is_arithmetic<T>::value, void>::type  deserialize_xml(T & object, const char * object_typename, const  char * XML_path);
	template<typename T> typename std::enable_if<std::is_arithmetic<T>::value, void>::type deserialize_xml(T & object, const char * object_typename, const char * XML_path, XMLDocument * ptr_doc, XMLElement * root);
	//string
	template<typename T> typename std::enable_if<std::is_same<std::string, T>::value, void>::type deserialize_xml(T & object, const char * object_typename, const char * XML_path, XMLDocument * ptr_doc, XMLElement * root);
	template<typename T> typename std::enable_if<std::is_same<std::string, T>::value, void>::type  deserialize_xml(T & object, const char * object_typename, const  char * XML_path);
	template<typename T> typename std::enable_if<std::is_same<std::string, T>::value, void>::type serialize_xml(T & object, const char * object_typename, const char * XML_path, XMLDocument * ptr_doc, XMLElement * root);
	template<typename T> typename std::enable_if<std::is_same<std::string, T>::value, void>::type serialize_xml(T & object, const char * object_typename, const char * XML_path);
	//vector
	template<typename T> void serialize_xml(vector<T> & object, const char * object_typename, const char * XML_path);
	template<typename T> void serialize_xml(vector<T> & object, const char * object_typename, const char * XML_path, XMLDocument * ptr_doc, XMLElement * root);
	template<typename T> void deserialize_xml(vector<T> & object, const char * object_typename, const  char * XML_path);
	template<typename T> void deserialize_xml(vector<T> & object, const char * object_typename, const  char * XML_path, XMLDocument * ptr_doc, XMLElement * root);
	//set
	template<typename T> void serialize_xml(set<T> & object, const char * object_typename, const char * XML_path);
	template<typename T> void serialize_xml(set<T> & object, const char * object_typename, const char * XML_path, XMLDocument * ptr_doc, XMLElement * root);
	template<typename T> void deserialize_xml(set<T> & object, const char * object_typename, const  char * XML_path);
	template<typename T> void deserialize_xml(set<T> & object, const char * object_typename, const  char * XML_path, XMLDocument * ptr_doc, XMLElement * root);
	//list
	template<typename T> void serialize_xml(list<T> & object, const char * object_typename, const char * XML_path);
	template<typename T> void serialize_xml(list<T> & object, const char * object_typename, const char * XML_path, XMLDocument * ptr_doc, XMLElement * root);
	template<typename T> void deserialize_xml(list<T> & object, const char * object_typename, const  char * XML_path);
	template<typename T> void deserialize_xml(list<T> & object, const char * object_typename, const  char * XML_path, XMLDocument * ptr_doc, XMLElement * root);
	//pair
	template<typename T1, typename T2> void serialize_xml(pair<T1, T2> & object, const char * object_typename, const char * XML_path);
	template<typename T1, typename T2> void serialize_xml(pair<T1, T2> & object, const char * object_typename, const char * XML_path, XMLDocument * ptr_doc, XMLElement * root);
	template<typename T1, typename T2> void deserialize_xml(pair<T1, T2> & object, const char * object_typename, const  char * XML_path);
	template<typename T1, typename T2> void deserialize_xml(pair<T1, T2> & object, const char * object_typename, const  char * XML_path, XMLDocument * ptr_doc, XMLElement * root);
	//map
	template<typename T1, typename T2> void serialize_xml(map<T1, T2> & object, const char * object_typename, const char * XML_path);
	template<typename T1, typename T2> void serialize_xml(map<T1, T2> & object, const char * object_typename, const char * XML_path, XMLDocument * ptr_doc, XMLElement * root);
	template<typename T1, typename T2> void deserialize_xml(map<T1, T2> & object, const char * object_typename, const  char * XML_path);
	template<typename T1, typename T2> void deserialize_xml(map<T1, T2> & object, const char * object_typename, const  char * XML_path, XMLDocument * ptr_doc, XMLElement * root);
	//struct
	template<typename T> typename std::enable_if<!std::is_arithmetic<T>::value && !std::is_same<std::string, T>::value, void>::type deserialize_xml(T & object, const char * object_typename, const char * XML_path);
	template<typename T> typename std::enable_if<!std::is_arithmetic<T>::value && !std::is_same<std::string, T>::value, void>::type serialize_xml(T & object, const char * object_typename, const char * XML_path);
	template<typename T>  typename std::enable_if<!std::is_arithmetic<T>::value && !std::is_same<std::string, T>::value, void>::type serialize_xml(T & object, const char * object_typename, const  char * XML_path, XMLDocument * ptr_doc, XMLElement * root);
	template<typename T>  typename std::enable_if<!std::is_arithmetic<T>::value && !std::is_same<std::string, T>::value, void>::type deserialize_xml(T & object, const char * object_typename, const  char * XML_path, XMLDocument * ptr_doc, XMLElement * root);
	template<size_t I, typename T> void recursive_fucking_serialize(T & object, const char * object_typename, const char * XML_path, XMLDocument * ptr_doc, XMLElement * root);
	template<size_t I, typename T> void recursive_fucking_deserialize(T & object, const char * object_typename, const char * XML_path, XMLDocument * ptr_doc, XMLElement * root);
	template<size_t I, typename T> constexpr decltype(auto) get(T&& t);
	template<size_t I, typename T1, typename T2> constexpr decltype(auto) put(T1&& t, T2 s);
	//smart pointer
	template<typename T>  void serialize_xml(shared_ptr<T> & object, const char * object_typename, const char * XML_path);
	template<typename T>  void serialize_xml(unique_ptr<T> & object, const char * object_typename, const char * XML_path);
	template<typename T>  void serialize_xml(weak_ptr<T> & object, const char * object_typename, const char * XML_path);
	template<typename T>  void deserialize_xml(shared_ptr<T> & object, const char * object_typename, const char * XML_path);
	template<typename T>  void deserialize_xml(unique_ptr<T> & object, const char * object_typename, const char * XML_path);
	template<typename T>  void deserialize_xml(weak_ptr<T> & object, const char * object_typename, const char * XML_path);
	//base64
	static inline bool is_base64(unsigned char c);
	string base64_encode(unsigned char const* buf, unsigned int bufLen);
	vector<unsigned char> base64_decode(string const&);
	void file_xml2base64(string file_name);
	void file_base642xml(string file_name);


	//=================================================
	//
	// function definition
	//
	//=================================================

	//========================================================================
	// shared function
	//========================================================================
	void create_XML(const char* XML_path) {
		remove(XML_path);
		// write the declearation of XML File
		const char* declaration = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>";
		XMLDocument doc;
		doc.Parse(declaration);

		// write the element of XML FIle
		XMLElement * current_root = doc.NewElement("serialization");
		doc.InsertEndChild(current_root);
		doc.SaveFile(XML_path);
	}

	//========================================================================
	// is_arithmetic type
	//========================================================================

	//============================
	// base type
	//============================
	template<typename T>
	typename std::enable_if<std::is_arithmetic<T>::value, void>::type
		serialize_xml(T & object, const char * object_typename, const char * XML_path) {
		create_XML(XML_path);
		XMLDocument doc;
		XMLDocument * ptr_doc = &doc;
		doc.LoadFile(XML_path);
		XMLElement * root = doc.RootElement();

		XMLElement * node = doc.NewElement(object_typename);

		root->LinkEndChild(node);

		stringstream stream;
		string object_string;
		stream << object;
		stream >> object_string;

		XMLText * node_text = doc.NewText(object_string.c_str());
		node->LinkEndChild(node_text);
		doc.SaveFile(XML_path);

		return;
	}

	//============================
	// recursive type
	//============================
	template<typename T>
	typename std::enable_if<std::is_arithmetic<T>::value, void>::type
		serialize_xml(T & object, const char * object_typename, const char * XML_path, XMLDocument * ptr_doc, XMLElement * root) {
		XMLElement * node = ptr_doc->NewElement(object_typename);
		root->LinkEndChild(node);

		stringstream stream;
		string object_string;
		stream << object;
		stream >> object_string;

		XMLText * node_text = ptr_doc->NewText(object_string.c_str());
		node->LinkEndChild(node_text);
		ptr_doc->SaveFile(XML_path);

		return;
	}

	//============================
	// base type
	//============================
	template<typename T> typename std::enable_if<std::is_arithmetic<T>::value, void>::type
		deserialize_xml(T & object, const char * object_typename, const  char * XML_path) {
		XMLDocument doc;
		int status = doc.LoadFile(XML_path);
		if (status != 0) {
			cout << "Error:Load " << XML_path << " file failed." << endl;
			return;
		}

		XMLElement* root = doc.RootElement()->FirstChildElement();
		string content = (string)(root->GetText());
		stringstream stream;
		stream << content;
		stream >> object;

		return;
	}


	//========================
	// recursive type
	//========================
	template<typename T>
	typename std::enable_if<std::is_arithmetic<T>::value, void>::type
		deserialize_xml(T & object, const char * object_typename, const  char * XML_path, XMLDocument * ptr_doc, XMLElement * root) {

		string content = (string)(root->GetText());
		stringstream stream;
		stream << content;
		stream >> object;

		return;
	}


	//========================================================================
	// string type
	//========================================================================


	//============================
	// base type
	//============================
	template<typename T>
	typename std::enable_if<std::is_same<std::string, T>::value, void>::type
		serialize_xml(T & object, const char * object_typename, const char * XML_path) {
		create_XML(XML_path);
		XMLDocument doc;
		XMLDocument * ptr_doc = &doc;
		doc.LoadFile(XML_path);
		XMLElement * root = doc.RootElement();

		XMLElement * node = doc.NewElement(object_typename);

		root->LinkEndChild(node);

		stringstream stream;
		string object_string;
		stream << object;
		stream >> object_string;

		XMLText * node_text = doc.NewText(object_string.c_str());
		node->LinkEndChild(node_text);
		doc.SaveFile(XML_path);

		return;
	}


	//========================
	// recursive type
	//========================
	template<typename T>
	typename std::enable_if<std::is_same<std::string, T>::value, void>::type
		serialize_xml(T & object, const char * object_typename, const char * XML_path, XMLDocument * ptr_doc, XMLElement * root) {
		XMLElement * node = ptr_doc->NewElement(object_typename);
		root->LinkEndChild(node);

		stringstream stream;
		string object_string;
		stream << object;
		stream >> object_string;

		XMLText * node_text = ptr_doc->NewText(object_string.c_str());
		node->LinkEndChild(node_text);
		ptr_doc->SaveFile(XML_path);

		return;
	}


	//=======================
	// base type
	//=======================
	template<typename T> typename std::enable_if<std::is_same<std::string, T>::value, void>::type
		deserialize_xml(T & object, const char * object_typename, const  char * XML_path) {
		XMLDocument doc;
		int status = doc.LoadFile(XML_path);
		if (status != 0) {
			cout << "Error:Load " << XML_path << " file failed." << endl;
			return;
		}

		XMLElement* root = doc.RootElement()->FirstChildElement();
		string content = (string)(root->GetText());
		stringstream stream;
		stream << content;
		stream >> object;

		return;
	}


	//========================
	// recursive type
	//========================
	template<typename T>
	typename std::enable_if<std::is_same<std::string, T>::value, void>::type
		deserialize_xml(T & object, const char * object_typename, const  char * XML_path, XMLDocument * ptr_doc, XMLElement * root) {

		string content = (string)(root->GetText());
		stringstream stream;
		stream << content;
		stream >> object;

		return;
	}


	//========================================================================
	//vector type
	//========================================================================

	//============================
	// recursive type
	//============================
	template<typename T>
	void serialize_xml(vector<T> & object, const char * object_typename, const char * XML_path, XMLDocument * ptr_doc, XMLElement * root) {
		XMLElement * node = ptr_doc->NewElement(object_typename);
		root->LinkEndChild(node);
		ptr_doc->SaveFile(XML_path);

		root = node;
		for (typename vector<T>::iterator i = object.begin(); i != object.end(); i++) {
			serialize_xml(*i, object_typename, XML_path, ptr_doc, root);
		}

		return;
	}


	//============================
	// base type
	//============================
	template<typename T>
	void serialize_xml(vector<T> & object, const char * object_typename, const char * XML_path) {
		create_XML(XML_path);
		XMLDocument doc;
		XMLDocument * ptr_doc = &doc;
		doc.LoadFile(XML_path);

		XMLElement * node = doc.NewElement(object_typename);
		XMLElement * root = doc.RootElement();
		root->LinkEndChild(node);
		doc.SaveFile(XML_path);

		root = node;
		for (typename vector<T>::iterator i = object.begin(); i != object.end(); i++) {
			serialize_xml(*i, object_typename, XML_path, ptr_doc, root);
		}

		return;
	}



	//========================
	// recursive type
	//========================
	template<typename T>
	void deserialize_xml(vector<T> & object, const char * object_typename, const  char * XML_path, XMLDocument * ptr_doc, XMLElement * root) {
		if (root == NULL) return;

		if (root->FirstChildElement()) {
			XMLElement * node = root->FirstChildElement();
			while (node) {
				T tmp;
				deserialize_xml(tmp, object_typename, XML_path, ptr_doc, node);
				object.push_back(tmp);
				node = node->NextSiblingElement();
			}
		}

		return;
	}


	//=======================
	// base type
	//=======================
	template<typename T>
	void deserialize_xml(vector<T> & object, const char * object_typename, const  char * XML_path) {
		XMLDocument doc;
		XMLDocument * ptr_doc = &doc;
		int status = doc.LoadFile(XML_path);
		if (status != 0) {
			cout << "Error:Load " << XML_path << " file failed." << endl;
			return;
		}

		XMLElement * root = doc.RootElement()->FirstChildElement();

		if (root->FirstChildElement()) {
			XMLElement * node = root->FirstChildElement();
			while (node) {
				T tmp;
				deserialize_xml(tmp, object_typename, XML_path, ptr_doc, node);
				object.push_back(tmp);
				node = node->NextSiblingElement();
			}
		}
		return;
	}


	//========================================================================
	//list type
	//========================================================================

	//============================
	// recursive type
	//============================
	template<typename T>
	void serialize_xml(list<T> & object, const char * object_typename, const char * XML_path, XMLDocument * ptr_doc, XMLElement * root) {
		XMLElement * node = ptr_doc->NewElement(object_typename);
		root->LinkEndChild(node);
		ptr_doc->SaveFile(XML_path);

		root = node;
		for (typename list<T>::iterator i = object.begin(); i != object.end(); i++) {
			serialize_xml(*i, object_typename, XML_path, ptr_doc, root);
		}

		return;
	}


	//============================
	// base type
	//============================
	template<typename T>
	void serialize_xml(list<T> & object, const char * object_typename, const char * XML_path) {
		create_XML(XML_path);
		XMLDocument doc;
		XMLDocument * ptr_doc = &doc;
		doc.LoadFile(XML_path);

		XMLElement * node = doc.NewElement(object_typename);
		XMLElement * root = doc.RootElement();
		root->LinkEndChild(node);
		doc.SaveFile(XML_path);

		root = node;
		for (typename list<T>::iterator i = object.begin(); i != object.end(); i++) {
			serialize_xml(*i, object_typename, XML_path, ptr_doc, root);
		}

		return;
	}



	//========================
	// recursive type
	//========================
	template<typename T>
	void deserialize_xml(list<T> & object, const char * object_typename, const  char * XML_path, XMLDocument * ptr_doc, XMLElement * root) {
		if (root == NULL) return;

		if (root->FirstChildElement()) {
			XMLElement * node = root->FirstChildElement();
			while (node) {
				T tmp;
				deserialize_xml(tmp, object_typename, XML_path, ptr_doc, node);
				object.push_back(tmp);
				node = node->NextSiblingElement();
			}
		}

		return;
	}


	//=======================
	// base type
	//=======================
	template<typename T>
	void deserialize_xml(list<T> & object, const char * object_typename, const  char * XML_path) {
		XMLDocument doc;
		XMLDocument * ptr_doc = &doc;
		int status = doc.LoadFile(XML_path);
		if (status != 0) {
			cout << "Error:Load " << XML_path << " file failed." << endl;
			return;
		}

		XMLElement * root = doc.RootElement()->FirstChildElement();

		if (root->FirstChildElement()) {
			XMLElement * node = root->FirstChildElement();
			while (node) {
				T tmp;
				deserialize_xml(tmp, object_typename, XML_path, ptr_doc, node);
				object.push_back(tmp);
				node = node->NextSiblingElement();
			}
		}
		return;
	}



	//========================================================================
	//set type
	//========================================================================

	//============================
	// recursive type
	//============================
	template<typename T>
	void serialize_xml(set<T> & object, const char * object_typename, const char * XML_path, XMLDocument * ptr_doc, XMLElement * root) {
		XMLElement * node = ptr_doc->NewElement(object_typename);
		root->LinkEndChild(node);
		ptr_doc->SaveFile(XML_path);

		root = node;
		for (typename set<T>::iterator i = object.begin(); i != object.end(); i++) {
			serialize_xml(*i, object_typename, XML_path, ptr_doc, root);
		}

		return;
	}


	//============================
	// base type
	//============================
	template<typename T>
	void serialize_xml(set<T> & object, const char * object_typename, const char * XML_path) {
		create_XML(XML_path);
		XMLDocument doc;
		XMLDocument * ptr_doc = &doc;
		doc.LoadFile(XML_path);

		XMLElement * node = doc.NewElement(object_typename);
		XMLElement * root = doc.RootElement();
		root->LinkEndChild(node);
		doc.SaveFile(XML_path);

		root = node;
		for (typename set<T>::iterator i = object.begin(); i != object.end(); i++) {
			serialize_xml(*i, object_typename, XML_path, ptr_doc, root);
		}

		return;
	}



	//========================
	// recursive type
	//========================
	template<typename T>
	void deserialize_xml(set<T> & object, const char * object_typename, const  char * XML_path, XMLDocument * ptr_doc, XMLElement * root) {
		if (root == NULL) return;

		if (root->FirstChildElement()) {
			XMLElement * node = root->FirstChildElement();
			while (node) {
				T tmp;
				deserialize_xml(tmp, object_typename, XML_path, ptr_doc, node);
				object.insert(tmp);
				node = node->NextSiblingElement();
			}
		}

		return;
	}


	//=======================
	// base type
	//=======================
	template<typename T>
	void deserialize_xml(set<T> & object, const char * object_typename, const  char * XML_path) {
		XMLDocument doc;
		XMLDocument * ptr_doc = &doc;
		int status = doc.LoadFile(XML_path);
		if (status != 0) {
			cout << "Error:Load " << XML_path << " file failed." << endl;
			return;
		}

		XMLElement * root = doc.RootElement()->FirstChildElement();

		if (root->FirstChildElement()) {
			XMLElement * node = root->FirstChildElement();
			while (node) {
				T tmp;
				deserialize_xml(tmp, object_typename, XML_path, ptr_doc, node);
				object.insert(tmp);
				node = node->NextSiblingElement();
			}
		}
		return;
	}



	//========================================================================
	//pair type
	//========================================================================

	//============================
	// recursive type
	//============================
	template<typename T1, typename T2>
	void serialize_xml(pair<T1, T2> & object, const char * object_typename, const char * XML_path, XMLDocument * ptr_doc, XMLElement * root) {
		XMLElement * node = ptr_doc->NewElement(object_typename);
		root->LinkEndChild(node);
		ptr_doc->SaveFile(XML_path);

		root = node;
		serialize_xml(object.first, "first", XML_path, ptr_doc, root);
		serialize_xml(object.second, "second", XML_path, ptr_doc, root);

		return;
	}


	//============================
	// base type
	//============================
	template<typename T1, typename T2>
	void serialize_xml(pair<T1, T2> & object, const char * object_typename, const char * XML_path) {
		create_XML(XML_path);
		XMLDocument doc;
		XMLDocument * ptr_doc = &doc;
		doc.LoadFile(XML_path);

		XMLElement * node = doc.NewElement(object_typename);
		XMLElement * root = doc.RootElement();
		root->LinkEndChild(node);
		doc.SaveFile(XML_path);

		root = node;
		serialize_xml(object.first, "first", XML_path, ptr_doc, root);
		serialize_xml(object.second, "second", XML_path, ptr_doc, root);

		return;
	}


	//========================
	// recursive type
	//========================
	template<typename T1, typename T2>
	void deserialize_xml(pair<T1, T2> & object, const char * object_typename, const  char * XML_path, XMLDocument * ptr_doc, XMLElement * root) {
		if (root == NULL) return;

		T1 tmp_first;
		T2 tmp_second;
		deserialize_xml(tmp_first, "first", XML_path, ptr_doc, root->FirstChildElement());
		deserialize_xml(tmp_second, "second", XML_path, ptr_doc, root->FirstChildElement()->NextSiblingElement());

		object = make_pair(tmp_first, tmp_second);

		return;
	}


	//=======================
	// base type
	//=======================
	template<typename T1, typename T2>
	void deserialize_xml(pair<T1, T2> & object, const char * object_typename, const  char * XML_path) {
		XMLDocument doc;
		XMLDocument * ptr_doc = &doc;
		int status = doc.LoadFile(XML_path);
		if (status != 0) {
			cout << "Error:Load " << XML_path << " file failed." << endl;
			return;
		}

		XMLElement * root = doc.RootElement()->FirstChildElement();

		T1 tmp_first;
		T2 tmp_second;
		deserialize_xml(tmp_first, "first", XML_path, ptr_doc, root->FirstChildElement());
		deserialize_xml(tmp_second, "second", XML_path, ptr_doc, root->FirstChildElement()->NextSiblingElement());

		object = make_pair(tmp_first, tmp_second);
		return;
	}





	//========================================================================
	//map type
	//========================================================================

	//============================
	// recursive type
	//============================
	template<typename T1, typename T2>
	void serialize_xml(map<T1, T2> & object, const char * object_typename, const char * XML_path, XMLDocument * ptr_doc, XMLElement * root) {
		XMLElement * node = ptr_doc->NewElement(object_typename);
		root->LinkEndChild(node);
		ptr_doc->SaveFile(XML_path);
		root = node;
		for (typename map<T1, T2>::iterator i = object.begin(); i != object.end(); ++i) {
			T1 tmp_first(i->first);
			T2 tmp_second(i->second);
			serialize_xml(tmp_first, "first", XML_path, ptr_doc, root);
			serialize_xml(tmp_second, "second", XML_path, ptr_doc, root);
		}

		return;
	}


	//============================
	// base type
	//============================
	template<typename T1, typename T2>
	void serialize_xml(map<T1, T2> & object, const char * object_typename, const char * XML_path) {
		create_XML(XML_path);
		XMLDocument doc;
		XMLDocument * ptr_doc = &doc;
		doc.LoadFile(XML_path);

		XMLElement * node = doc.NewElement(object_typename);
		XMLElement * root = doc.RootElement();
		root->LinkEndChild(node);
		doc.SaveFile(XML_path);

		root = node;
		for (typename map<T1, T2>::iterator i = object.begin(); i != object.end(); i++) {
			T1 tmp_first(i->first);
			T2 tmp_second(i->second);
			serialize_xml(tmp_first, "first", XML_path, ptr_doc, root);
			serialize_xml(tmp_second, "second", XML_path, ptr_doc, root);
		}

		return;
	}



	//========================
	// recursive type
	//========================
	template<typename T1, typename T2>
	void deserialize_xml(map<T1, T2> & object, const char * object_typename, const  char * XML_path, XMLDocument * ptr_doc, XMLElement * root) {
		if (root == NULL) return;

		if (root->FirstChildElement()) {
			XMLElement * node = root->FirstChildElement();
			while (node) {
				T1 tmp_first;
				T2 tmp_second;
				pair<T1, T2> tmp_pair;
				deserialize_xml(tmp_first, "first", XML_path, ptr_doc, node);
				node = node->NextSiblingElement();
				deserialize_xml(tmp_second, "second", XML_path, ptr_doc, node);
				node = node->NextSiblingElement();
				tmp_pair = make_pair(tmp_first, tmp_second);
				object.insert(tmp_pair);

			}
		}

		return;
	}


	//=======================
	// base type
	//=======================
	template<typename T1, typename T2>
	void deserialize_xml(map<T1, T2> & object, const char * object_typename, const  char * XML_path) {
		XMLDocument doc;
		XMLDocument * ptr_doc = &doc;
		int status = doc.LoadFile(XML_path);
		if (status != 0) {
			cout << "Error:Load " << XML_path << " file failed." << endl;
			return;
		}

		XMLElement * root = doc.RootElement()->FirstChildElement();

		if (root->FirstChildElement()) {
			XMLElement * node = root->FirstChildElement();
			while (node) {
				T1 tmp_first;
				T2 tmp_second;
				pair<T1, T2> tmp_pair;
				deserialize_xml(tmp_first, "first", XML_path, ptr_doc, node);
				node = node->NextSiblingElement();
				deserialize_xml(tmp_second, "second", XML_path, ptr_doc, node);
				node = node->NextSiblingElement();
				tmp_pair = make_pair(tmp_first, tmp_second);
				object.insert(tmp_pair);
			}
		}
		return;
	}


	//=====================
	// struct type
	//=====================



	//=======================
	// help function
	//=======================

	// get a varable of the type of the  same struct submember
	template<size_t I = 0, typename T>
	constexpr decltype(auto) get(T&& t) {
		using M = decltype(get_reflect_members(std::forward<T>(t)));
		auto s = std::forward<T>(t).*(std::get<I>(M::apply_impl()));
		return s;
	}

	// assign a variable to the same struct submember
	template<size_t I = 0, typename T1, typename T2>
	constexpr decltype(auto) put(T1&& t, T2 s) {
		using M = decltype(get_reflect_members(std::forward<T1>(t)));
		std::forward<T1>(t).*(std::get<I>(M::apply_impl())) = s;
		return;
	}

	// solve the std::get<I> I cannot be variable problem
	template<size_t I = 0, typename T>
	void recursive_fucking_serialize(T & object, const char * object_typename, const char * XML_path, XMLDocument * ptr_doc, XMLElement * root) {
		auto catch_result = get<I>(object);

		serialize_xml(catch_result, object_typename, XML_path, ptr_doc, root);

		using M = decltype(get_reflect_members(std::forward<T>(object)));
		if constexpr (I + 1 != std::tuple_size< decltype(M::apply_impl()) >::value) {
			recursive_fucking_serialize<I + 1>(object, object_typename, XML_path, ptr_doc, root);
		}
		return;
	}

	template<size_t I = 0, typename T>
	void recursive_fucking_deserialize(T & object, const char * object_typename, const char * XML_path, XMLDocument * ptr_doc, XMLElement * root) {
		auto catch_result = get<I>(object);

		deserialize_xml(catch_result, object_typename, XML_path, ptr_doc, root);
		put<I>(object, catch_result);

		root = root->NextSiblingElement();

		using M = decltype(get_reflect_members(std::forward<T>(object)));
		if constexpr (I + 1 != std::tuple_size< decltype(M::apply_impl()) >::value) {
			recursive_fucking_deserialize<I + 1>(object, object_typename, XML_path, ptr_doc, root);
		}
		return;
	}



	//=======================
	// base type
	//=======================

	template<typename T>
	typename std::enable_if<!std::is_arithmetic<T>::value && !std::is_same<std::string, T>::value, void>::type
		serialize_xml(T & object, const char * object_typename, const  char * XML_path) {
		create_XML(XML_path);
		XMLDocument doc;
		XMLDocument * ptr_doc = &doc;
		doc.LoadFile(XML_path);
		XMLElement * root = doc.RootElement();

		XMLElement * node = doc.NewElement(object_typename);

		root->LinkEndChild(node);

		root = node;

		recursive_fucking_serialize(object, object_typename, XML_path, ptr_doc, root);

		doc.SaveFile(XML_path);
		return;
	}


	//=======================
	// base type
	//=======================
	template<typename T>
	typename std::enable_if<!std::is_arithmetic<T>::value && !std::is_same<std::string, T>::value, void>::type
		deserialize_xml(T & object, const char * object_typename, const char * XML_path) {
		XMLDocument doc;
		XMLDocument * ptr_doc = &doc;
		int status = doc.LoadFile(XML_path);
		if (status != 0) {
			cout << "Error:Load " << XML_path << " file failed." << endl;
			return;
		}

		XMLElement * root = doc.RootElement()->FirstChildElement();

		if (root->FirstChildElement()) {
			XMLElement * node = root->FirstChildElement();

			recursive_fucking_deserialize(object, object_typename, XML_path, ptr_doc, node);
		}
		return;
	}


	//================
	//recursive type
	//================

	template<typename T>
	typename std::enable_if<!std::is_arithmetic<T>::value && !std::is_same<std::string, T>::value, void>::type
		serialize_xml(T & object, const char * object_typename, const  char * XML_path, XMLDocument * ptr_doc, XMLElement * root) {

		XMLElement * node = ptr_doc->NewElement(object_typename);
		root->LinkEndChild(node);
		ptr_doc->SaveFile(XML_path);

		root = node;

		recursive_fucking_serialize(object, object_typename, XML_path, ptr_doc, node);

		return;
	}

	//================
	//recursive type
	//================
	template<typename T>
	typename std::enable_if<!std::is_arithmetic<T>::value && !std::is_same<std::string, T>::value, void>::type
		deserialize_xml(T & object, const char * object_typename, const  char * XML_path, XMLDocument * ptr_doc, XMLElement * root) {
		if (root == NULL) return;

		if (root->FirstChildElement()) {
			XMLElement * node = root->FirstChildElement();
			recursive_fucking_deserialize(object, object_typename, XML_path, ptr_doc, node);
		}
		return;
	}




	//============================
	// smart pointer
	// overload limited types of pointer
	//============================

	//============================
	// serialize smart pointer
	//============================

	template<typename T>
	void serialize_xml(shared_ptr<T> & object, const char * object_typename, const char * XML_path) {
		create_XML(XML_path);
		XMLDocument doc;
		XMLDocument * ptr_doc = &doc;
		doc.LoadFile(XML_path);
		XMLElement * root = doc.RootElement();

		XMLElement * node = doc.NewElement(object_typename);

		root->LinkEndChild(node);

		root = node;

		serialize_xml(*object, object_typename, XML_path, ptr_doc, root);
		doc.SaveFile(XML_path);

		return;
	}

	template<typename T>
	void serialize_xml(weak_ptr<T> & object, const char * object_typename, const char * XML_path) {
		create_XML(XML_path);
		XMLDocument doc;
		XMLDocument * ptr_doc = &doc;
		doc.LoadFile(XML_path);
		XMLElement * root = doc.RootElement();

		XMLElement * node = doc.NewElement(object_typename);

		root->LinkEndChild(node);

		root = node;

		shared_ptr<T> shared_object = object.lock();

		serialize_xml(*shared_object, object_typename, XML_path, ptr_doc, root);

		doc.SaveFile(XML_path);

		return;
	}

	template<typename T>
	void serialize_xml(unique_ptr<T> & object, const char * object_typename, const char * XML_path) {
		create_XML(XML_path);
		XMLDocument doc;
		XMLDocument * ptr_doc = &doc;
		doc.LoadFile(XML_path);
		XMLElement * root = doc.RootElement();

		XMLElement * node = doc.NewElement(object_typename);

		root->LinkEndChild(node);

		root = node;


		serialize_xml(*object, object_typename, XML_path, ptr_doc, root);

		doc.SaveFile(XML_path);
		return;
	}

	//============================
	// deserialize smart pointer
	//============================

	template<typename T>
	void deserialize_xml(unique_ptr<T> & object, const char * object_typename, const char * XML_path) {

		XMLDocument doc;
		XMLDocument * ptr_doc = &doc;
		int status = doc.LoadFile(XML_path);
		if (status != 0) {
			cout << "Error:Load " << XML_path << " file failed." << endl;
			return;
		}

		XMLElement * root = doc.RootElement()->FirstChildElement();
		if (root->FirstChildElement()) {
			XMLElement * node = root->FirstChildElement();

			T ptr_element;

			deserialize_xml(ptr_element, object_typename, XML_path, ptr_doc, node);

			object = std::make_unique<T>(ptr_element);
		}
		return;
	}


	template<typename T>
	void deserialize_xml(shared_ptr<T> & object, const char * object_typename, const char * XML_path) {

		XMLDocument doc;
		XMLDocument * ptr_doc = &doc;
		int status = doc.LoadFile(XML_path);
		if (status != 0) {
			cout << "Error:Load " << XML_path << " file failed." << endl;
			return;
		}

		XMLElement * root = doc.RootElement()->FirstChildElement();
		if (root->FirstChildElement()) {
			XMLElement * node = root->FirstChildElement();

			T ptr_element;

			deserialize_xml(ptr_element, object_typename, XML_path, ptr_doc, node);

			object = std::make_shared<T>(ptr_element);
		}
		return;
	}


	template<typename T>
	void deserialize_xml(weak_ptr<T> & object, const char * object_typename, const char * XML_path) {
		XMLDocument doc;
		XMLDocument * ptr_doc = &doc;
		int status = doc.LoadFile(XML_path);
		if (status != 0) {
			cout << "Error:Load " << XML_path << " file failed." << endl;
			return;
		}

		XMLElement * root = doc.RootElement()->FirstChildElement();
		if (root->FirstChildElement()) {
			XMLElement * node = root->FirstChildElement();

			T ptr_element;

			deserialize_xml(ptr_element, object_typename, XML_path, ptr_doc, node);

			shared_ptr<T> shared_ptr = std::make_shared<T>(ptr_element);

			object = shared_ptr;
		}

		return;
	}


	//========================================
	// base64
	//========================================


	//===================
	// dictionary
	//===================
	static const std::string base64_chars =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789+/";

	static inline bool is_base64(unsigned char c) {
		return (isalnum(c) || (c == '+') || (c == '/'));
	}

	//===================
	// encode & decode
	//===================
	std::string base64_encode(unsigned char const* buf, unsigned int bufLen) {
		std::string ret;
		int i = 0;
		int j = 0;
		unsigned char char_array_3[3];
		unsigned char char_array_4[4];

		while (bufLen--) {
			char_array_3[i++] = *(buf++);
			if (i == 3) {
				char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
				char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
				char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
				char_array_4[3] = char_array_3[2] & 0x3f;

				for (i = 0; (i < 4); i++)
					ret += base64_chars[char_array_4[i]];
				i = 0;
			}
		}

		if (i)
		{
			for (j = i; j < 3; j++)
				char_array_3[j] = '\0';

			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (j = 0; (j < i + 1); j++)
				ret += base64_chars[char_array_4[j]];

			while ((i++ < 3))
				ret += '=';
		}

		return ret;
	}

	std::vector<unsigned char> base64_decode(std::string const& encoded_string) {
		int in_len = encoded_string.size();
		int i = 0;
		int j = 0;
		int in_ = 0;
		unsigned char char_array_4[4], char_array_3[3];
		std::vector<unsigned char> ret;

		while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
			char_array_4[i++] = encoded_string[in_]; in_++;
			if (i == 4) {
				for (i = 0; i < 4; i++)
					char_array_4[i] = base64_chars.find(char_array_4[i]);

				char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
				char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
				char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

				for (i = 0; (i < 3); i++)
					ret.push_back(char_array_3[i]);
				i = 0;
			}
		}

		if (i) {
			for (j = i; j < 4; j++)
				char_array_4[j] = 0;

			for (j = 0; j < 4; j++)
				char_array_4[j] = base64_chars.find(char_array_4[j]);

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (j = 0; (j < i - 1); j++) ret.push_back(char_array_3[j]);
		}
		return ret;
	}


	//===================
	// interface with file
	//===================
	void file_xml2base64(string file_name) {
		ifstream inFile(file_name);
		std::string str((std::istreambuf_iterator<char>(inFile)),
			std::istreambuf_iterator<char>());
		vector<unsigned char> vector_byte;
		for (int i = 0; i < str.size(); i++) {
			vector_byte.push_back((unsigned char)str[i]);
		}
		string base64_str = base64_encode(&vector_byte[0], vector_byte.size());
		cout << "base64 code : " << endl;
		cout << base64_str;
		ofstream outFile(file_name, fstream::out | ios_base::trunc);
		outFile << base64_str;
	}


	void file_base642xml(string file_name) {
		ifstream inFile(file_name);
		std::string str((std::istreambuf_iterator<char>(inFile)),
			std::istreambuf_iterator<char>());

		vector<unsigned char> vector_byte = base64_decode(str);
		cout << "xml code :" << endl;
		for (int i = 0; i < vector_byte.size(); i++) {
			cout << vector_byte[i];
		}

		string xml_output(vector_byte.begin(), vector_byte.end());
		ofstream outFile(file_name, fstream::out | ios_base::trunc);
		outFile << xml_output;
	}



}

#endif