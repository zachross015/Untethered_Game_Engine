#ifndef FUNCTIONHOLDER_H
#define FUNCTIONHOLDER_H
#include <vector>
/////////////////////////////////////////////////////////////////////////////////
// The purpose of this class is to provide a template class for all
// vectors of functions to be ran
//
// Copyright © 2016 Zachary Ross. All rights reserved.
/////////////////////////////////////////////////////////////////////////////////

namespace zr
{
	template<typename Func>
	class FunctionHolder
	{
	public:
		//
		// Default class constructor
		//
		FunctionHolder() {};

		//
		// Function that adds a function with type F to the vector
		// of functions
		// @param function is the function to be added
		//
		void add(Func function);

		//
		// Function that returns the size of the functions vector
		// @result returns the amount of objects in the vector
		//
		std::size_t size();

		//
		// Function that gets the function at the index specified
		// @result returns the function at that index
		//
		Func get(int index);

		//
		// Function that deletes all functions in the vector
		//
		void deleteAllFunctions();

		//
		// Function that deletes the specified function
		// @param function is the function to be deleted
		//
		void deleteFunction(Func function);

		//
		// Function that deletes the function at the specified index
		// @param index is the index of the function to be deleted
		//
		void deleteFunction(int index);

	private:
		std::vector<Func> functions;
		int amt = 0;
	};

	template<typename Func>
	void FunctionHolder<Func>::add(Func f)
	{
		functions.push_back(f);
		amt += 1;
	}

	template<typename Func>
	std::size_t FunctionHolder<Func>::size()
	{
		return amt;
	}

	template<typename Func>
	Func FunctionHolder<Func>::get(int index)
	{
		return functions[index];
	}

	template<typename Func>
	void FunctionHolder<Func>::deleteFunction(Func f)
	{
		auto obj = std::find(functions.begin(), functions.end(), f);
		if (obj != functions.end())
		{
			functions.erase(obj);
			amt -= 1;
		}
		//delete *obj;
	}

	template<typename Func>
	void FunctionHolder<Func>::deleteFunction(int index)
	{
		deleteFunction(functions[index]);
	}

	template<typename Func>
	void FunctionHolder<Func>::deleteAllFunctions()
	{
		for (int index = functions.size() - 1; index > 0; index--)
			deleteFunction(functions[index]);
	}
}
#endif
