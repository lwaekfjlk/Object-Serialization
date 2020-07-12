#include"binary_serialize.h"
#include"xml_serialize.h"

/*
	本文件实现测试功能
*/
using namespace std;
using namespace binary_serialize;
using namespace xml_serialize;
struct Person
{
	vector<string> name;
	int         age;
	double      salary;
	vector<vector<double>> a;
};
REFLECTION(Person, name, age, salary, a)

struct Substruct {
	int a;
	int b;
};
struct Mystruct {
	Substruct substruct;
	double c;
};

REFLECTION(Mystruct, substruct, c)
REFLECTION(Substruct, a, b)


struct Test_Sub_Struct {
	int _int;
	double _double;
	string _string;
	vector<double> _vector;
	set<bool> _set;
	pair<string, char> _pair;
	map<double, int> _map;
	pair<vector<vector<vector<int> > >, map<set<double>, list<bool> > > _nest_pair;
};
REFLECTION(Test_Sub_Struct, _int, _double, _string, _vector, _set, _pair, _map, _nest_pair)

struct Test_Struct {
	int _int;
	double _double;
	string _string;
	vector<double> _vector;
	set<bool> _set;
	pair<string, char> _pair;
	map<double, int> _map;
	pair<vector<vector<vector<int> > >, map<set<double>, list<bool> > > _nest_pair;
	Test_Sub_Struct _sub_struct;
};
REFLECTION(Test_Struct, _int, _double, _string, _vector, _set, _pair, _map, _nest_pair, _sub_struct)


int main() {


	//============================
	 // test std::is_arithmetic
	 //============================

	int _int = 1, __int, ___int;
	double _double = 0.1, __double, ___double;
	bool _bool = true, __bool, ___bool;
	float _float = 0.1, __float, ___float;
	char _char = 'c', __char, ___char;
	short _short = 1, __short, ___short;
	long long _longlong = 1000, __longlong, ___longlong;
	//int
	serialize(_int, "int.data");
	deserialize(__int, "int.data");
	cout << "int_binary: " << (_int == __int) << endl;
	serialize_xml(_int, "int", "int.xml");
	deserialize_xml(___int, "int", "int.xml");
	cout << "int_xml: " << (_int == ___int) << endl;

	//double
	serialize(_double, "double.data");
	deserialize(__double, "double.data");
	cout << "double_binary: " << (_double == __double) << endl;
	serialize_xml(_double, "double", "double.xml");
	deserialize_xml(___double, "double", "double.xml");
	cout << "double_xml: " << (_double == ___double) << endl;
	//bool
	serialize(_bool, "bool.data");
	deserialize(__bool, "bool.data");
	cout << "bool_binary: " << (_bool == __bool) << endl;
	serialize_xml(_bool, "bool", "bool.xml");
	deserialize_xml(___bool, "bool", "bool.xml");
	cout << "bool_xml: " << (_bool == ___bool) << endl;
	//float
	serialize(_float, "float.data");
	deserialize(__float, "float.data");
	cout << "float_binary: " << (_float == __float) << endl;
	serialize_xml(_float, "float", "float.xml");
	deserialize_xml(___float, "float", "float.xml");
	cout << "float_xml: " << (_float == ___float) << endl;
	//char
	serialize(_char, "char.data");
	deserialize(__char, "char.data");
	cout << "char_binary: " << (_char == __char) << endl;
	serialize_xml(_char, "char", "char.xml");
	deserialize_xml(___char, "char", "char.xml");
	cout << "char_xml: " << (_char == ___char) << endl;
	//short
	serialize(_short, "short.data");
	deserialize(__short, "short.data");
	cout << "short_binary: " << (_short == __short) << endl;
	serialize_xml(_short, "short", "short.xml");
	deserialize_xml(___short, "short", "short.xml");
	cout << "short_xml: " << (_short == ___short) << endl;
	//longlong
	serialize(_longlong, "longlong.data");
	deserialize(__longlong, "longlong.data");
	cout << "longlong_binary: " << (_longlong == __longlong) << endl;
	serialize_xml(_longlong, "longlong", "longlong.xml");
	deserialize_xml(___longlong, "longlong", "longlong.xml");
	cout << "longlong_xml: " << (_longlong == ___longlong) << endl;


	//============================
	//test std::string
	//============================
	string _string = "hello,world";
	string __string, ___string;
	serialize(_string, "string.data");
	deserialize(__string, "string.data");
	cout << "string_binary: " << (_string == __string) << endl;
	serialize_xml(_string, "string", "string.xml");
	deserialize_xml(___string, "string", "string.xml");
	cout << "string_xml: " << (_string == ___string) << endl;


	//============================
	//test std::STL
	//============================
	vector<double> _vector = { 1,2,3,4,5 };
	vector<double> __vector, ___vector;
	list<int> _list = { 1,2,3,4,5 };
	list<int> __list, ___list;
	set<bool> _set = { true,false };
	set<bool> __set, ___set;
	pair<string, char> _pair, __pair, ___pair;
	_pair = make_pair("OOP", 'c');
	map<double, int> _map, __map, ___map;
	_map[3.14] = 0;

	//vector
	serialize(_vector, "vector.data");
	deserialize(__vector, "vector.data");
	cout << "vector_binary: " << (_vector == __vector) << endl;
	serialize_xml(_vector, "vector", "vector.xml");
	deserialize_xml(___vector, "vector", "vector.xml");
	cout << "vector_xml: " << (_vector == ___vector) << endl;

	//list
	serialize(_list, "list.data");
	deserialize(__list, "list.data");
	cout << "list_binary: " << (_list == __list) << endl;
	serialize_xml(_list, "list", "list.xml");
	deserialize_xml(___list, "list", "list.xml");
	cout << "list_xml: " << (_list == ___list) << endl;

	//set
	serialize(_set, "set.data");
	deserialize(__set, "set.data");
	cout << "set_binary: " << (_set == __set) << endl;
	serialize_xml(_set, "set", "set.xml");
	deserialize_xml(___set, "set", "set.xml");
	cout << "set_xml: " << (_set == ___set) << endl;

	//map
	serialize(_map, "map.data");
	deserialize(__map, "map.data");
	cout << "map_binary: " << (_map == __map) << endl;
	serialize_xml(_map, "map", "map.xml");
	deserialize_xml(___map, "map", "map.xml");
	cout << "map_xml: " << (_map == ___map) << endl;

	//pair
	serialize(_pair, "pair.data");
	deserialize(__pair, "pair.data");
	cout << "pair_binary: " << (_pair == __pair) << endl;
	serialize_xml(_pair, "pair", "pair.xml");
	deserialize_xml(___pair, "pair", "pair.xml");
	cout << "pair_xml: " << (_pair == ___pair) << endl;

	//test a extremely complex example
	//construct pair<vector<vector<vector<int> > > ,map<set<double>,list<bool> > >
	pair<vector<vector<vector<int> > >, map<set<double>, list<bool> > > _nest_pair, __nest_pair, ___nest_pair;

	vector<vector<vector<int> > > _pair_first = { {{1,2,3},{4,5,6}},{{7,8,9}} };
	set<double> _map_first = { 0.1,0.2,0.3 };
	list<bool> _map_second = { false,true,false };
	map<set<double>, list<bool> > _pair_second;
	_pair_second[_map_first] = _map_second;
	_nest_pair = make_pair(_pair_first, _pair_second);

	serialize(_nest_pair, "nest_pair.data");
	deserialize(___nest_pair, "nest_pair.data");
	cout << "nest_pair_binary: " << (_nest_pair == ___nest_pair) << endl;

	serialize_xml(_nest_pair, "nest_pair", "nest_pair.xml");
	deserialize_xml(__nest_pair, "nest_pair", "nest_pair.xml");
	cout << "nest_pair_xml: " << (_nest_pair == __nest_pair) << endl;




	//============================
	//test user defined struct
	//============================

	Test_Sub_Struct _sub_struct = { _int,_double,_string,_vector,_set,_pair,_map,_nest_pair };;
	Test_Sub_Struct __sub_struct, ___sub_struct;
	Test_Struct _struct = { _int,_double,_string,_vector,_set,_pair,_map,_nest_pair,_sub_struct };
	Test_Struct __struct, ___struct;


	// need vs compiler to avoid segment fault

	/*
	serialize(_sub_struct, "sub_struct.data");
	deserialize(___sub_struct, "sub_struct.data");
	cout
		<< "sub_struct_binary: "
		<< ((_sub_struct._int == ___sub_struct._int) &&
		(_sub_struct._double == ___sub_struct._double) &&
			(_sub_struct._string == ___sub_struct._string) &&
			(_sub_struct._vector == ___sub_struct._vector) &&
			(_sub_struct._set == ___sub_struct._set) &&
			(_sub_struct._pair == ___sub_struct._pair) &&
			(_sub_struct._map == ___sub_struct._map) &&
			(_sub_struct._nest_pair == ___sub_struct._nest_pair)
			)
		<< endl;
	*/


	serialize_xml(_sub_struct, "sub_struct", "sub_struct.xml");
	deserialize_xml(__sub_struct, "sub_struct", "sub_struct.xml");
	cout
		<< "sub_struct_xml: "
		<< ((_sub_struct._int == __sub_struct._int) &&
		(_sub_struct._double == __sub_struct._double) &&
			(_sub_struct._string == __sub_struct._string) &&
			(_sub_struct._vector == __sub_struct._vector) &&
			(_sub_struct._set == __sub_struct._set) &&
			(_sub_struct._pair == __sub_struct._pair) &&
			(_sub_struct._map == __sub_struct._map) &&
			(_sub_struct._nest_pair == __sub_struct._nest_pair)
			)
		<< endl;

	// need vs compiler to avoid segment fault

	/*
	serialize(_struct, "struct.data");
	deserialize(___struct, "struct.data");
	cout
		<< "struct_binary: "
		<< ((_struct._int == ___struct._int) &&
		(_struct._double == ___struct._double) &&
			(_struct._string == ___struct._string) &&
			(_struct._vector == ___struct._vector) &&
			(_struct._set == ___struct._set) &&
			(_struct._pair == ___struct._pair) &&
			(_struct._map == ___struct._map) &&
			(_struct._nest_pair == ___struct._nest_pair)
			)
		<< endl;
	*/

	serialize_xml(_struct, "struct", "struct.xml");
	deserialize_xml(__struct, "struct", "struct.xml");
	cout
		<< "struct_xml: "
		<< ((_struct._int == __struct._int) &&
		(_struct._double == __struct._double) &&
			(_struct._string == __struct._string) &&
			(_struct._vector == __struct._vector) &&
			(_struct._set == __struct._set) &&
			(_struct._pair == __struct._pair) &&
			(_struct._map == __struct._map) &&
			(_struct._nest_pair == __struct._nest_pair)
			)
		<< endl;





	//====================================
	// test struct as element to be nested
	//====================================
	vector<Test_Struct> _vector_struct, __vector_struct, ___vector_struct;
	_vector_struct.push_back(_struct);


	// need vs compiler to avoid segment fault
	/*
	cout << "hello,world"<<endl;
	serialize(_vector_struct, "vector_struct.data");
	deserialize(___vector_struct, "vector_struct.data");
	cout
		<< "vector_struct_binary: "
		<< ((_vector_struct[0]._int == ___vector_struct[0]._int) &&
		(_vector_struct[0]._double == ___vector_struct[0]._double) &&
			(_vector_struct[0]._string == ___vector_struct[0]._string) &&
			(_vector_struct[0]._vector == ___vector_struct[0]._vector) &&
			(_vector_struct[0]._set == ___vector_struct[0]._set) &&
			(_vector_struct[0]._pair == ___vector_struct[0]._pair) &&
			(_vector_struct[0]._map == ___vector_struct[0]._map) &&
			(_vector_struct[0]._nest_pair == ___vector_struct[0]._nest_pair) &&
			(_vector_struct[0]._sub_struct._double == ___vector_struct[0]._sub_struct._double) &&
			(_vector_struct[0]._sub_struct._int == ___vector_struct[0]._sub_struct._int) &&
			(_vector_struct[0]._sub_struct._map == ___vector_struct[0]._sub_struct._map) &&
			(_vector_struct[0]._sub_struct._nest_pair == ___vector_struct[0]._sub_struct._nest_pair) &&
			(_vector_struct[0]._sub_struct._pair == ___vector_struct[0]._sub_struct._pair) &&
			(_vector_struct[0]._sub_struct._set == ___vector_struct[0]._sub_struct._set) &&
			(_vector_struct[0]._sub_struct._string == ___vector_struct[0]._sub_struct._string) &&
			(_vector_struct[0]._sub_struct._vector == ___vector_struct[0]._sub_struct._vector)
			)
		<< endl;
	*/

	serialize_xml(_vector_struct, "vector_struct", "vector_struct.xml");
	deserialize_xml(__vector_struct, "vector_struct", "vector_struct.xml");

	cout
		<< "vector_struct_xml: "
		<< ((_vector_struct[0]._int == __vector_struct[0]._int) &&
		(_vector_struct[0]._double == __vector_struct[0]._double) &&
			(_vector_struct[0]._string == __vector_struct[0]._string) &&
			(_vector_struct[0]._vector == __vector_struct[0]._vector) &&
			(_vector_struct[0]._set == __vector_struct[0]._set) &&
			(_vector_struct[0]._pair == __vector_struct[0]._pair) &&
			(_vector_struct[0]._map == __vector_struct[0]._map) &&
			(_vector_struct[0]._nest_pair == __vector_struct[0]._nest_pair) &&
			(_vector_struct[0]._sub_struct._double == __vector_struct[0]._sub_struct._double) &&
			(_vector_struct[0]._sub_struct._int == __vector_struct[0]._sub_struct._int) &&
			(_vector_struct[0]._sub_struct._map == __vector_struct[0]._sub_struct._map) &&
			(_vector_struct[0]._sub_struct._nest_pair == __vector_struct[0]._sub_struct._nest_pair) &&
			(_vector_struct[0]._sub_struct._pair == __vector_struct[0]._sub_struct._pair) &&
			(_vector_struct[0]._sub_struct._set == __vector_struct[0]._sub_struct._set) &&
			(_vector_struct[0]._sub_struct._string == __vector_struct[0]._sub_struct._string) &&
			(_vector_struct[0]._sub_struct._vector == __vector_struct[0]._sub_struct._vector)
			)
		<< endl;



	map<double, vector<Test_Struct> > _map_struct, __map_struct, ___map_struct;
	_map_struct[3.14] = _vector_struct;

	// need vs compiler to avoid segment fault

	/*
	serialize(_map_struct, "map_struct.data");
	deserialize(___map_struct, "map_struct.data");
	cout
		<< "map_struct_binary: "
		<< ((_map_struct[3.14][0]._int == ___map_struct[3.14][0]._int) &&
		(_map_struct[3.14][0]._double == ___map_struct[3.14][0]._double) &&
			(_map_struct[3.14][0]._string == ___map_struct[3.14][0]._string) &&
			(_map_struct[3.14][0]._vector == ___map_struct[3.14][0]._vector) &&
			(_map_struct[3.14][0]._set == ___map_struct[3.14][0]._set) &&
			(_map_struct[3.14][0]._pair == ___map_struct[3.14][0]._pair) &&
			(_map_struct[3.14][0]._map == ___map_struct[3.14][0]._map) &&
			(_map_struct[3.14][0]._nest_pair == ___map_struct[3.14][0]._nest_pair)
			)
		<< endl;
	*/

	serialize_xml(_map_struct, "map_struct", "map_struct.xml");
	deserialize_xml(__map_struct, "map_struct", "map_struct.xml");
	cout
		<< "map_struct_xml: "
		<< ((_map_struct[3.14][0]._int == __map_struct[3.14][0]._int) &&
		(_map_struct[3.14][0]._double == __map_struct[3.14][0]._double) &&
			(_map_struct[3.14][0]._string == __map_struct[3.14][0]._string) &&
			(_map_struct[3.14][0]._vector == __map_struct[3.14][0]._vector) &&
			(_map_struct[3.14][0]._set == __map_struct[3.14][0]._set) &&
			(_map_struct[3.14][0]._pair == __map_struct[3.14][0]._pair) &&
			(_map_struct[3.14][0]._map == __map_struct[3.14][0]._map) &&
			(_map_struct[3.14][0]._nest_pair == __map_struct[3.14][0]._nest_pair)
			)
		<< endl;


	list<struct Test_Struct>_list_struct{ _struct };
	list<struct Test_Struct>__list_struct, ___list_struct;

	// need vs compiler to avoid segment fault


	typename list<struct Test_Struct>::iterator  i = _list_struct.begin();
	typename list<struct Test_Struct>::iterator  j = __list_struct.begin();
	/*
	
	serialize(_list_struct, "list_struct.data");
	deserialize(__list_struct, "list_struct.data");
	cout
		<< "list_struct_binary: "
		<< (((*i)._int == (*j)._int) &&
		((*i)._double == (*j)._double) &&
			((*i)._string == (*j)._string) &&
			((*i)._vector == (*j)._vector) &&
			((*i)._set == (*j)._set) &&
			((*i)._pair == (*j)._pair) &&
			((*i)._map == (*j)._map) &&
			((*i)._nest_pair == (*j)._nest_pair) &&
			((*i)._sub_struct._double == (*j)._sub_struct._double) &&
			((*i)._sub_struct._int == (*j)._sub_struct._int) &&
			((*i)._sub_struct._map == (*j)._sub_struct._map) &&
			((*i)._sub_struct._nest_pair == (*j)._sub_struct._nest_pair) &&
			((*i)._sub_struct._pair == (*j)._sub_struct._pair) &&
			((*i)._sub_struct._set == (*j)._sub_struct._set) &&
			((*i)._sub_struct._string == (*j)._sub_struct._string) &&
			((*i)._sub_struct._vector == (*j)._sub_struct._vector)
			)
		<< endl;
	*/

	serialize_xml(_list_struct, "list_struct", "list_struct.xml");
	deserialize_xml(___list_struct, "list_struct", "list_struct.xml");

	j = ___list_struct.begin();

	cout
		<< "list_struct_xml: "
		<< (((*i)._int == (*j)._int) &&
		((*i)._double == (*j)._double) &&
			((*i)._string == (*j)._string) &&
			((*i)._vector == (*j)._vector) &&
			((*i)._set == (*j)._set) &&
			((*i)._pair == (*j)._pair) &&
			((*i)._map == (*j)._map) &&
			((*i)._nest_pair == (*j)._nest_pair) &&
			((*i)._sub_struct._double == (*j)._sub_struct._double) &&
			((*i)._sub_struct._int == (*j)._sub_struct._int) &&
			((*i)._sub_struct._map == (*j)._sub_struct._map) &&
			((*i)._sub_struct._nest_pair == (*j)._sub_struct._nest_pair) &&
			((*i)._sub_struct._pair == (*j)._sub_struct._pair) &&
			((*i)._sub_struct._set == (*j)._sub_struct._set) &&
			((*i)._sub_struct._string == (*j)._sub_struct._string) &&
			((*i)._sub_struct._vector == (*j)._sub_struct._vector)
			)
		<< endl;




	//smart pointer

	std::shared_ptr < std::vector<std::vector<std::string>> > _share_ptr1(new  std::vector<std::vector<std::string>>{ {"1232","456"},{"123","2342523","23425","23535"},{"3545324","2342r","34254","342624"} });
	std::shared_ptr < std::vector<std::vector<std::string>> > _share_ptr2(new  std::vector<std::vector<std::string>>);
	std::shared_ptr< std::vector<std::vector<std::string>> > _share_ptr3(new  std::vector<std::vector<std::string>>);
	



	//unique

	std::unique_ptr < std::vector<std::vector<std::string>> > _unique_ptr1(new  std::vector<std::vector<std::string>>{ {"1232","456"},{"123","2342523","23425","23535"},{"3545324","2342r","34254","342624"} });
	std::unique_ptr < std::vector<std::vector<std::string>> > _unique_ptr2(new  std::vector<std::vector<std::string>>);
	std::unique_ptr < std::vector<std::vector<std::string>> > _unique_ptr3(new  std::vector<std::vector<std::string>>);


	serialize(_unique_ptr1, "n.data");
	deserialize(_unique_ptr2, "n.data");

	cout << "smart_unique_binary: " << ((*_unique_ptr1) == (*_unique_ptr2)) << endl;


	serialize_xml(_unique_ptr1, "smart_unique", "smart_unique.xml");
	deserialize_xml(_unique_ptr3, "smart_unique", "smart_unique.xml");

	cout << "smart_unique_xml: " << ((*_unique_ptr1) == (*_unique_ptr3)) << endl;


	//shared_ptr
	serialize(_share_ptr1, "n.data");
	deserialize(_share_ptr2, "n.data");

	cout << "smart_shared_binary: " << ((*_share_ptr1) == (*_share_ptr2)) << endl;

	serialize_xml(_share_ptr1, "smart_shared", "smart_shared.xml");
	deserialize_xml(_share_ptr3, "smart_shared", "smart_shared.xml");

	cout << "smart_shared_xml: " << ((*_share_ptr1) == (*_share_ptr3)) << endl;

	cout << endl << endl << endl << endl << "==================================================" << endl;
	
	//===============================
    //base64  test
    //===============================
    file_xml2base64("map_struct.xml");
    file_base642xml("map_struct.xml");

	return 0;

}
