# Map module

## `map` class structure and principles

### Entry
Map holds technical fields, which are just extansional: filenames of data, used to initialize class instance:
```    
    QLatin1String svgMapFileName; 
    QLatin1String mapInfoFileName; 
```    
Also it contains two the most important objects: svg_view* instance, which contains an actual mall map an used for drawing purposes and graph* instance, which is used for routing within mall.
```    
    svg_view* pic;
    graph* paths;
```   
Those entities are created by svg_viever and graph modules respectively: picture is downloaded from file and graph is build based on svg picture - so the implementation of _Init..._ functions is none of maps buiseness.

<a name="shops_data_in_map"></a>Also, there are extra data (e.g. hours of work, shop descriptions, shop title, etc), which is stored by shops_data* instance. Access to this data is provided by the class methods. Note that access to infromatition related to one exact object is given by its shop_data* instance inner id (quint32), so there is an object_indexes field, containing map objects XML_ID and inner id respectively.         
```  
    shops_data* info;
    QMap<QLatin1String, quint32> object_indexes; 
```   
### Public methods
First one returns object index, needed to access its data via shops_data* entity, based on argument `id` = XML_ID of an object.
```
    quint32 GetIndex(QLatin1String id); 
```
Second one provides quick check whether the object is registered in `shops_data* info`
```
    bool Exists (QLatin1String id); // checks if the object exists
```
**NOTE: Always check whether the object exists before trying to get its index**

Third map method provides whole [`shops_data* info`](#shops_data_in_map) pointer. Yes, its unsafe. Althought there is no way to do it safe and fast (copying QString's with unknown length might be hell)
```
shops_data* GetInfo (void);
```
**NOTE: DO NOT MODIFY DATA HANGING ON THE OTHER SIDE OF POINTER YOU GET THIS WAY. IT WILL HURT.**

### Signals
```
    void MapPictureChanged(svg_view * view);
    void PathGraphChanged(graph * graph);
    void MapInfoChanged(shops_data const * const & info, QMap<QLatin1String, quint32> indexes);
```
Those are just functions that provide access on change of inner fields. Bieng connected to the slots of classes, using the map, they should provide fresh and up-to-date information related to map.

**NOTE: `svg_view * view` and `graph * graph` might be nullptr. Care! Check!**

### Slots
```
    void SetAnotherMap(QString const & mapToSet, QString const & extrasToSet);
```
Recieves the titles of new svg picture file (default svg file with SVD_ID's assigned to all objects) and extra map [information file](#Information-file)

# Additional information

## `shops_data` module

### `shops_data` entry

Class holds an array (in case of string values - a list) of object parameters^
```
    QStringList shortName;
    bool* isUnique;
    QStringList shortInfo;
    QTime* opensAt;
    QTime* closesAt;
    QStringList fullInfo;
```
E.g. `isUnique[1]` is value of `isUnique` parameter of the second object on the map. Indexes are stored ([object_indexes](#shops_data_in_map)) at class, holding instance of shops_entry.
Those fields are just some data related to mall shop's features.


In case we need not set of whole data but only the information related to the one exact object, 

### `shops_data` public methods
<a name="Access"></a>
```
template<typename T> void Access(T*& toSet, data_accessable what_needed, quint32 index = QUINT_MAX);
```
This method allow to acces any parameter of any object by its `index` and set variable on `toSet` pointer, passed to the function to that parameter's value. In case no index provided, the whole pointer is set (**NOTE: MEMORY LEAKS INCOMING**) to the related **array/list** of shops_data.
NOTE: [data_accessable](#data_accessable) `what_needed` value must correspond with `toSet` pointer type `T`.
NOTE: Though it should be obvious, NEVER TRY TO EDIT DATA U'VE GOT IN CASE YOU CALLED Access WITHOUT `index` parameter! READ ONLY.

### Public module functions
```
void DestroyInfo (shops_data *& i);
shops_data* InitInfoFromFile(QString const & file, QMap<QLatin1String, quint32>& indexes);
```
First one is used to release memory, deleting `shops_data` instance.
The second one is responsible for [xml-file](#Information-file) parsing - and creating `shops_data` instance also.

### Module defines
<a name="data_accessable"></a>
```
enum data_accessable
{
    DA_SVG_ID=0,
    DA_SHORT_NAME,
    DA_IS_UNIQUE,
    DA_SHORT_INFO,
    DA_OPENS_AT,
    DA_CLOSES_AT,
    DA_FULL_INFO
};
```
Is used to set which parameter is needed while calling the [Access](#Access) method.

## Information file
This file is generated automaticly with xml-schema via microsoft excel
xml schema used:
<details>
  
```
  <?xml version="1.0" encoding="utf-8"?>
<xs:schema xmlns:xs="http://www.w3.org/2001/XMLSchema">

	<xs:element name="Info">
		<xs:complexType>
			<xs:sequence maxOccurs="1">
				<xs:element name="size" type ="xs:unsignedInt" />
				<xs:sequence>
					<xs:element ref="InfoLine" minOccurs="0" maxOccurs="unbounded"/>
				</xs:sequence>
			</xs:sequence>
		</xs:complexType>
	</xs:element>
	
	<xs:element name ="InfoLine">
		<xs:complexType>
			<xs:sequence>
				<xs:element name="SVG_ID" type ="xs:string" />
				<xs:element name="short_name" type ="xs:string" />
				<xs:element name="is_a_shop" type="xs:boolean" />
				<xs:element name="short_info" type ="xs:string" minOccurs="0" />
				<xs:element name="opens" type ="xs:time" minOccurs="0" />
				<xs:element name="closes" type ="xs:time" minOccurs="0" />
				<xs:element name="full_info" type ="xs:string" minOccurs="0" />
			</xs:sequence>
		</xs:complexType>
	</xs:element>
</xs:schema>
```
</details>
The sample of file generated:    
<details>
  
```
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<Info>
	<size>2</size>
	<InfoLine>
		<SVG_ID>shop1_1</SVG_ID>
		<short_name>fancy diamond shop!</short_name>
		<is_a_shop>true</is_a_shop>
		<short_info>I've made it look like a description</short_info>
		<opens>09:05:00.000</opens>
		<closes>19:05:00.000</closes>
		<full_info>The best shop ever!
The best shop ever!
The best shop ever!
The best shop ever!
The best shop ever!</full_info>
	</InfoLine>
	<InfoLine>
		<SVG_ID>shop1_2</SVG_ID>
		<short_name>poor rectangle</short_name>
		<is_a_shop>true</is_a_shop>
		<short_info>The standard Lorem Ipsum passage, used since the 1500s</short_info>
		<opens>09:05:00.000</opens>
		<closes>19:05:00.000</closes>
		<full_info>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.</full_info>
	</InfoLine>
</Info>
```
</details>    
    
    
    
    
