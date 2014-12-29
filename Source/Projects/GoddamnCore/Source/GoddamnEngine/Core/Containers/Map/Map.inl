/// ==========================================================================================
/// Map.h - Dynamically sized associative vectors interfacs.
/// Copyright (C) $(GODDAMN_DEV) 2011 - Present. All Rights Reserved.
/// 
/// History:
///		* --.06.2013 - Created by James Jhuighuy
///		* 05.05.2014 - Rewritten from scratch by James Jhuighuy
/// ==========================================================================================

#if (!defined(GD_CORE_CONTAINERS_MAP))
#	error "Attempting to include 'UnorderedMap.inl' file. Please, use 'UnorderedMap.h' instead."
#endif	// if (!defined(GD_CORE_CONTAINERS_MAP))

GD_NAMESPACE_BEGIN
	
#if (!defined(GD_DOCUMENTATION))
	// Namespace contains some default predicates used by map class.
	namespace UnorderedMapPrivate
	{
		// Default searching predicate based on comparing to pairs by key.
		template<typename KeyType, typename ValueType>
		struct ByKeySearchingPredicateType final
		{
		private:
			GD_CLASS_UNASSIGNABLE(ByKeySearchingPredicateType);
			GD_CLASS_UNCOPIABLE  (ByKeySearchingPredicateType);
			KeyType const* const Key = nullptr;

		public:
			GDINL ByKeySearchingPredicateType(KeyType const& Key) : Key(&Key) { }
			GDINL bool operator() (Pair<KeyType, ValueType> const& Pair) const { return ((*this->Key) == Pair.Key); }
		};	// struct ByKeySearchingPredicateType 
	}	// namespace UnorderedMapPrivate
#endif	// if (!defined(GD_DOCUMENTATION))

	/// ==========================================================================================
	/// UnorderedMap class
	/// ==========================================================================================

#define GD_UNORDERED_MAP_TEMPLATE() template<typename KeyType, typename ValueType, typename MemoryProviderType /* = VectorMemoryProviders::HeapMemoryProvider<Pair<KeyType, ValueType>> */>
#define GD_UNORDERED_MAP_CLASS()    UnorderedMap<KeyType, ValueType,  MemoryProviderType>
#define GD_UNORDERED_MAP_BASE()     Vector<Pair <KeyType, ValueType>, MemoryProviderType>
	
	GD_UNORDERED_MAP_TEMPLATE()
	GDINL GD_UNORDERED_MAP_CLASS()::UnorderedMap(size_t const InitialElemntsCount /* = 0 */, size_t const Capacity /* = SIZE_MAX */)
		: GD_UNORDERED_MAP_BASE ()(InitialElemntsCount, Capacity) { }

	GD_UNORDERED_MAP_TEMPLATE()
	GDINL GD_UNORDERED_MAP_CLASS()::UnorderedMap(ConstIterator const StartIterator, ConstIterator const EndIterator)
		: GD_UNORDERED_MAP_BASE ()(StartIterator, EndIterator) { }

	GD_UNORDERED_MAP_TEMPLATE()
	GDINL GD_UNORDERED_MAP_CLASS()::UnorderedMap(std::initializer_list<ThisPairType> const& InitializerList)
		: GD_UNORDERED_MAP_BASE ()(InitializerList) { }

	GD_UNORDERED_MAP_TEMPLATE()
	GDINL GD_UNORDERED_MAP_CLASS()::UnorderedMap(UnorderedMap&& OtherMap)
		: GD_UNORDERED_MAP_BASE ()(Forward(OtherMap)) { }

	GD_UNORDERED_MAP_TEMPLATE()
	GDINL GD_UNORDERED_MAP_CLASS()::UnorderedMap(UnorderedMap const& OtherMap)
		: GD_UNORDERED_MAP_BASE ()(OtherMap) { }

#if (defined(__cplusplus_cli))
	GD_UNORDERED_MAP_TEMPLATE()
	GDINL GD_UNORDERED_MAP_CLASS()::UnorderedMap(array<ThisPairType>^ CliArray)
		: GD_UNORDERED_MAP_BASE ()(CliArray)
	{
	}
#endif	// if (defined(__cplusplus_cli))

	GD_UNORDERED_MAP_TEMPLATE()
	GDINL void GD_UNORDERED_MAP_CLASS()::PushLast(KeyType const& Key, ValueType const& Value)
	{
		this->GD_UNORDERED_MAP_BASE()::PushLast(ThisPairType(Key, Value));
	}

	GD_UNORDERED_MAP_TEMPLATE()
	GDINL size_t GD_UNORDERED_MAP_CLASS()::FindFirstElement(KeyType const& Key) const
	{	// We have a predicate to make search by comparing all pairs by keys.
		return this->GD_UNORDERED_MAP_BASE()::FindFirstElement(UnorderedMapPrivate::ByKeySearchingPredicateType<KeyType, ValueType>(Key));
	}

	GD_UNORDERED_MAP_TEMPLATE()
	GDINL size_t GD_UNORDERED_MAP_CLASS()::FindLastElement(KeyType const& Key) const
	{	// We have a predicate to make search by comparing all pairs by keys.
		return this->GD_UNORDERED_MAP_BASE()::FindLastElement(UnorderedMapPrivate::ByKeySearchingPredicateType<KeyType, ValueType>(Key));
	}

	GD_UNORDERED_MAP_TEMPLATE()
	GDINL GD_UNORDERED_MAP_CLASS()& GD_UNORDERED_MAP_CLASS()::operator= (UnorderedMap&& OtherMap)
	{
		this->GD_UNORDERED_MAP_BASE()::operator=(Forward(OtherMap));
		return (*this);
	}

	GD_UNORDERED_MAP_TEMPLATE()
	GDINL GD_UNORDERED_MAP_CLASS()& GD_UNORDERED_MAP_CLASS()::operator= (UnorderedMap const& OtherMap)
	{
		this->GD_UNORDERED_MAP_BASE()::operator=(OtherMap);
		return (*this);
	}

	GD_UNORDERED_MAP_TEMPLATE()
	GDINL GD_UNORDERED_MAP_CLASS()& GD_UNORDERED_MAP_CLASS()::operator= (std::initializer_list<ThisPairType> const& InitializerList)
	{
		this->GD_UNORDERED_MAP_BASE()::operator=(InitializerList);
		return (*this);
	}

#if (defined(__cplusplus_cli))
	GD_UNORDERED_MAP_TEMPLATE()
	GDINL GD_UNORDERED_MAP_CLASS()& GD_UNORDERED_MAP_CLASS()::operator= (array<ThisPairType>^ CliArray)
	{
		this->GD_UNORDERED_MAP_BASE()::operator=(CliArray);
		return (*this);
	}
#endif	// if (defined(__cplusplus_cli))

	GD_UNORDERED_MAP_TEMPLATE()
	GDINL ValueType const& GD_UNORDERED_MAP_CLASS()::operator[] (KeyType const& Key) const
	{
		size_t const Index = this->FindFirstElement(Key);
		if (Index == SIZE_MAX)
		{
			this->PushLast(ThisPairType());
			return this->GetLastElement().Value;
		}

		return *this->GetElementAt(Index).Value;
	}

	GD_UNORDERED_MAP_TEMPLATE()
	GDINL ValueType& GD_UNORDERED_MAP_CLASS()::operator[] (KeyType const& Key)
	{
		return const_cast<ValueType&>(const_cast<ThisUnorderedMapType const&>(*this)[Key]);
	}

#undef GD_UNORDERED_MAP_TEMPLATE
#undef GD_UNORDERED_MAP_CLASS
#undef GD_UNORDERED_MAP_BASE
GD_NAMESPACE_END