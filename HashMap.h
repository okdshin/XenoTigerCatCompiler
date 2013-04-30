#pragma once
//HashMap:20130430
#include <iostream>
#include <vector>
#include <cassert>
#include <stdexcept>
#include <boost/format.hpp>
#include "SharedPtr.h"
#include "Function.h"

namespace tiger_cat
{
template<class Key, class Value>
class HashMap{
public:
	class Element{
	public:
		using Ptr = SharedPtr<Element>;
		static auto Create(const Key& key, const Value& value) -> Ptr {
			return Ptr(new Element(key, value));	
		}
		auto GetKey()const -> Key { return key;	}
		auto GetValue()const -> Value { return value; }
		auto IsLast()const -> bool {
			return !static_cast<bool>(next_element);	
		}
		auto GetNextElement()const -> Ptr {
			assert(IsLast() == false);
			return next_element;	
		}
		auto SetNextElement(const Ptr& next_element) -> void {
			assert(IsLast() == true);
			this->next_element = next_element;	
		}

		friend auto operator<<(
				std::ostream& os, 
				HashMap<Key, Value>::Element element) -> std::ostream&{
			os << "[";
			while(true){
				os << boost::format("(Key:%1%, Value:%2%)") 
					% element.key
					% element.value;
				if(element.IsLast()){
					os << "]";
					break;	
				}
				os << ", ";
				element = *element.GetNextElement();
			}
			return os;	
		}
	private:
		Element(const Key& key, const Value& value) : key(key), value(value) {}
		Key key;
		Value value;
		Ptr next_element;
	};

    HashMap(
		unsigned int table_size, 
		const std::function<unsigned int(const Key&)>& arg_id_index_calculator) :
			id_index_calculator([this, arg_id_index_calculator](
					const Key& key) -> unsigned int {
				return arg_id_index_calculator(key) % element_vect.size(); 
			}), 
			element_vect(table_size){}

	auto Insert(const Key& key, const Value& value) -> void {
		const auto new_element = Element::Create(key, value);
		const auto id_index = id_index_calculator(key);
		if(!static_cast<bool>(element_vect.at(id_index))){
			element_vect.at(id_index) = new_element;
		}
		else{
			auto element = element_vect.at(id_index);
			while(true){
				if(element->IsLast()){
					break;	
				}
				element = element->GetNextElement();
			}
			element->SetNextElement(new_element);
		}
	}

	auto Find(const Key& key)const -> typename Element::Ptr {
		const auto id_index = id_index_calculator(key);
		assert(0 <= id_index && id_index < element_vect.size());
		auto element = element_vect.at(id_index_calculator(key));
		if(!static_cast<bool>(element)){
			//throw std::out_of_range("no such key element."); 	
			return typename Element::Ptr();
		}
		while(element->GetKey() != key){
			if(element->IsLast()){
				//throw std::out_of_range("no such key element."); 	
				return typename Element::Ptr();
			}
			element = element->GetNextElement();
		}
		return element;	
	}
	
	friend auto operator<<(
			std::ostream& os, const HashMap<Key, Value>& hash_map) -> std::ostream&{
		for(const auto& element : hash_map.element_vect){
			if(element){
				os << boost::format("{IdIndex:%1%, ") 
					% hash_map.id_index_calculator(element->GetKey());
				os << *element << "}" << std::endl;
			}
			else{
				os << "empty" << std::endl;	
			}
		}
		return os;	
	}
private:
	std::function<unsigned int(const Key&)> id_index_calculator;
	std::vector<typename Element::Ptr> element_vect;

};

}

