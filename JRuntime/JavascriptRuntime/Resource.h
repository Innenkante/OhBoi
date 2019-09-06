#pragma once
#include <map>

//Resource containing the recourse in an array
//Created over a static constructor returning the index of the rescource
//clean up the rescourse by the index
class Resource
{
public:
	Resource() {}
	Resource(void* pointerToResource);




	static int AddResource(Resource resource);
	static void RemoveResource(int index);
	static int GetCurrentIndex();
private:
	void* resourcePointer;
	void Clear();
	static std::map<int, Resource> resources;
};

