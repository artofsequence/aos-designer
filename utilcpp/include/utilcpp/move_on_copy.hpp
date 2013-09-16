#ifndef HGUARD_UTILCXX_MOVE_ON_COPY_HPP__
#define HGUARD_UTILCXX_MOVE_ON_COPY_HPP__

#include <utility>

namespace util
{
	template<typename T>
	struct move_on_copy_wrapper
	{
		mutable T value;

		move_on_copy_wrapper():
			value()
		{}

		move_on_copy_wrapper(T&& t):
			value(std::move(t))
		{}

		move_on_copy_wrapper(move_on_copy_wrapper const& other):
			value(std::move(other.value))
		{}

		move_on_copy_wrapper(move_on_copy_wrapper&& other):
			value(std::move(other.value))
		{}

		move_on_copy_wrapper& operator=(move_on_copy_wrapper const& other)
		{
			value=std::move(other.value);
			return *this;
		}

		move_on_copy_wrapper& operator=(move_on_copy_wrapper&& other)
		{
			value=std::move(other.value);
			return *this;
		}

	};
}


#endif
