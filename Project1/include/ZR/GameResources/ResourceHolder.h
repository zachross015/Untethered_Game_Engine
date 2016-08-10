//
//  ResourceHolder.h
//  New Game
//
//  Created by Zachary Ross on 9/18/15.
//  Copyright (c) 2015 Zachary Ross. All rights reserved.
//

#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>
#include <map>
#include <memory>
#include <SFML\Audio.hpp>

namespace zr
{
	template <typename Resource, typename Identifier>
	class ResourceHolder
	{
	public:
		ResourceHolder();

		void                    load(Identifier id, const std::string& filename);

		Resource&               get(Identifier id);
		const Resource&         get(Identifier id) const;
	private:
		std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
	};

	template <typename Resource, typename Identifier>
	ResourceHolder<Resource, Identifier>::ResourceHolder()
	{

	}

	template <typename Resource, typename Identifier>
	void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
	{
		std::string aFName; //actual file name for mac
		std::unique_ptr<Resource> resource(new Resource());
		aFName = filename;

		if (!resource->loadFromFile(aFName))
			throw std::runtime_error("ResourceHolder::load - Failed to load " + aFName);
		if(mResourceMap.find(id) == mResourceMap.end())
		{
			auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
			assert(inserted.second);
		}
	}

	template <typename Resource, typename Identifier>
	Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
	{
		auto found = mResourceMap.find(id);
		assert(found != mResourceMap.end());
		return *found->second;
	}
}



#endif 
