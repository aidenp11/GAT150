//#pragma once
//#include <memory>
//#include "Singleton.h"
//#include <map>
//#include <string>
//
//namespace kiko
//{
//	class CreatorBase
//	{
//	public:
//		virtual ~CreatorBase() = default;
//
//		virtual std::unique_ptr<class Oject> Create() = 0;
//	};
//
//	template <typename T>
//	class Creator : public CreatorBase
//	{
//		virtual std::unique_ptr<class Oject> Create() override
//		{
//			return std::make_unique<T>();
//		}
//	};
//
//	class Factory : public Singleton<Factory>
//	{
//	public:
//
//	private:
//		std::map<std::string, std::unique_ptr<CreatorBase>> m_registry;
//
//	};
//}
