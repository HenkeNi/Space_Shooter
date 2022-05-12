#pragma once
#include <memory>

template <typename Resource, typename Identifier>
class ResourceManager
{
public:
	ResourceManager() = default;

	template		<typename... Args>
	void			Load(Identifier aId, Args&&... args);
	Resource&		GetResource(Identifier aId);
	const Resource& GetResource(Identifier aId) const;
	void			InsertResource(Identifier aId, std::unique_ptr<Resource> aResource);

private:
	std::unordered_map<Identifier, std::unique_ptr<Resource>> m_resources;
};

template <typename Resource, typename Identifier>
template <typename... Args>
void ResourceManager<Resource, Identifier>::Load(Identifier aId, Args&&... args)
{
	auto resource{ std::make_unique<Resource>() };

	if (!resource->loadFromFile(std::forward<Args>(args)...))
		throw std::runtime_error("Failed to load resource!\n");

	InsertResource(aId, std::move(resource));
}

template <typename Resource, typename Identifier>
Resource& ResourceManager<Resource, Identifier>::GetResource(Identifier aId)
{
	auto found{ m_resources.find(aId) };
	assert(found != m_resources.end());

	return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceManager<Resource, Identifier>::GetResource(Identifier aId) const
{
	auto found{ m_resources.find(aId) };
	assert(found != m_resources.end());

	return *found->second;
}

template <typename Resource, typename Identifier>
void ResourceManager<Resource, Identifier>::InsertResource(Identifier aId, std::unique_ptr<Resource> aResource)
{
	auto inserted{ m_resources.insert(std::make_pair(aId, std::move(aResource))) };
	assert(inserted.second);
}
