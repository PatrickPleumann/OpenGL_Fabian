#pragma once
#include <glad/glad.h>
#include <functional>
#include <memory>

class Resource
{
public:
	Resource(GLuint id, std::function<void(GLuint)> callOnDelete) : m_id{ id }, m_callOnDelete{ callOnDelete } {}

	~Resource()
	{
		m_callOnDelete(m_id);
	}
	Resource(const Resource&) = delete;
	Resource& operator =(const Resource&) = delete;

	Resource(const Resource&&) = delete;
	Resource& operator =(const Resource&&) = delete;
	GLuint operator*() const
	{
		return m_id;
	}
private:
	GLuint m_id;
	std::function<void(GLuint)> m_callOnDelete;
};


class UniqueResource
{
public:
	UniqueResource(GLuint id, std::function<void(GLuint)> callOnDelete)
		: m_resource{ std::make_unique<Resource>(id, callOnDelete) } {}

	GLuint operator*() const
	{
		return **m_resource;
	}

private:
	std::unique_ptr<Resource> m_resource;
};

