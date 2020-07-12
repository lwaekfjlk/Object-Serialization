# Recro

![license](https://img.shields.io/github/license/:user/:repo.svg)
![](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)

**Recro** is a simple wrapper module that achieves both **XML** and **binary** serialization. It is developed in C++17.

## Background

This project is motivated by the final project of **Object Oriented Programming** Course in ZJU.

This library is designed to use pure recursive approaches to simplify serialization in a portable cross-platform manner.

In this project, two **namespaces** *xml_serialize*,  *binary_serialize*  are included separately in *xml_serialize.h* file and *binary_serialize.h* file.

* **xml_serialize** developed by Haofei YU and act as a wrapper module of  **tinyxml** 
* **binary_serialize** developed by Jianhao Fu



## Running Tips



####Windows

All testing codes are tested on Visual Studio 2019 and files added to the VS project can be run directly.

#### macOS / Linux

Change to the current directory and use the following command to build the project.

[part of the function in *binary_serialize* namespace only supports Visual Studio Compiler and g++ Compiler can turn out to have **Segment Fault**]

```bash
$ g++ test.cpp tinyxml.cpp -std=c++17
```



## Usage

Full testing and examples can be found in *test.cpp*.



Supported serialization object type includes:

* std::is_arithmetic
* std::string + its nested type
* std::map,std::list,std::vector,std::set,std::pair + their nested type + their combined type
* std::shared_ptr,std::unique_ptr
* user defined struct with members less than 30 + its nested type + its combined type



Serialization results can be:

* XML file (*.xml)
* binary file (*.data)
* Base64 file (*.xml) *[encoded from and decoded to XML file available]*



## Tutorial

Objects of common types can be serialized directly.

One possible instance is:

```c++
pair<vector<vector<vector<int> > > ,map<set<double>,list<bool> > > _nest_pair,__nest_pair,___nest_pair;

// fill the content in the initial _nest_pair object
// ....

// change _nest_pair into XML file
xml_serialize::serialize_xml(_nest_pair,"nest_pair","nest_pair.xml");
xml_serialize::deserialize_xml(__nest_pair,"nest_pair","nest_pair.xml");

// change _nest_pair into binary file
binary_serialize::serialize(_nest_pair,"nest_pair.data");
binary_serialize::deserialize(___nest_pair,"nest_pair.data");

// test the result
cout << "nest_pair_xml: "<<(_nest_pair == __nest_pair) << endl;
cout << "nest_pair_binary: "<<(_nest_pair == ___nest_pair) <<endl;
```



Objects of User Defined Struct type needs users to input the meta data in *REFLECTION(...)* .

*REFLECTION(...)* is a marco predefined in *xml_serialize.h* file and is used to store the meta data of the struct in order to achieve reflection in C++.

One possible instance is :

```c++
// struct must be defined as global variable
struct Test_Sub_Struct{
    int _int;
    double _double;
    string _string;
    vector<double> _vector;
    set<bool> _set;
    pair<string,char> _pair;
    map<double,int> _map;
    pair<vector<vector<vector<int> > > ,map<set<double>,list<bool> > > _nest_pair;
};
REFLECTION(Test_Sub_Struct,_int,_double,_string,_vector,_set,_pair,_map,_nest_pair)

struct Test_Struct{
    int _int;
    double _double;
    string _string;
    vector<double> _vector;
    set<bool> _set;
    pair<string,char> _pair;
    map<double,int> _map;
    pair<vector<vector<vector<int> > > ,map<set<double>,list<bool> > > _nest_pair;
    Test_Sub_Struct _sub_struct;
};
REFLECTION(Test_Struct,_int,_double,_string,_vector,_set,_pair,_map,_nest_pair,_sub_struct)
  

// use user defined struct

// translate struct into binary file
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

// translate struct into xml file
serialize_xml(_struct,"struct","struct.xml");
deserialize_xml(__struct,"struct","struct.xml");
cout
  << "struct_xml: "
  <<( (_struct._int == __struct._int) &&
     (_struct._double == __struct._double) &&
     (_struct._string == __struct._string) &&
     (_struct._vector == __struct._vector) &&
     (_struct._set == __struct._set) &&
     (_struct._pair == __struct._pair) &&
     (_struct._map == __struct._map) &&
     (_struct._nest_pair == __struct._nest_pair)
    )
  <<endl;

```



Also support encode and decode between string mode XML file and base64 mode XML file.

Using this function by:

```C++
file_xml2base64("myxml.xml");
file_base642xml("myxml.xml");
```



## Possible Flaw

* Compiling it by g++ receives Segment Fault
* <name> ...</name>  in the XML file is not precisely defined and does not have explicit meanings.
* Do not support weak_ptr<T> in smart pointer type



## Contributing

PRs accepted.



## License

MIT © lwaekfjlk