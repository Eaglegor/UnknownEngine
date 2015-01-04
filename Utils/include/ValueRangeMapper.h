#pragma once

namespace UnknownEngine
{
	namespace Utils
	{
		template <typename T>
		class ValueRangeMapper
		{
		public:
			
			static_assert(std::is_floating_point<T>::value, "Only floating point types may be used");
			
			ValueRangeMapper(T lowest_raw_value, T highest_raw_value, T lowest_mapped_value, T highest_mapped_value):
			lowest_raw_value(lowest_raw_value),
			highest_raw_value(highest_raw_value),
			lowest_mapped_value(lowest_mapped_value),
			highest_mapped_value(highest_mapped_value),
			raw_range_inversed( 1 / (highest_raw_value - lowest_raw_value) ),
			mapped_range(highest_mapped_value - lowest_mapped_value)
			{}
			
			T getMappedValue(T raw_value)
			{
				if(raw_value < lowest_raw_value) return lowest_mapped_value;
				if(raw_value > highest_raw_value) return highest_mapped_value;
				return lowest_mapped_value + mapped_range * ( raw_value - lowest_raw_value ) * raw_range_inversed;
			}
			
		private:
			T lowest_raw_value;
			T highest_raw_value;
			T lowest_mapped_value;
			T highest_mapped_value;
			T raw_range_inversed;
			T mapped_range;
		};
	}
}