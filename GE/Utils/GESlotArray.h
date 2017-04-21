#pragma once


//
//
//
// CGEArray -	Basic resizable slot array - A slot array differs from a normal array in that the array is not shrank and elements are not compacted when elements are removed. Instead 
//					array elements that are removed are marked with NULL. With this, the Length of the array denotes the total number of items added to the array and not the number of valid 
//					elements. To get the number of valid elements call count()
//
//
//
template <class T>
class CGESlotArray
{
	// Properties
protected:
	int		Growth;			// Number of elements to grow array when we run out of space
public:
	void	setGrowth(int growth) { Growth = growth; }
	int		getSize() const { return Size; }
	// Properties End
protected:
	T*		Elements;		// Array elements
	int		Size;			// Max size of array
	int		LastFreedSlot;	// Slot that was last freed

public:
	CGESlotArray()
	{
		LastFreedSlot = 0;
		Growth = 4;
		Size = 4;
		Elements = new T[Size]();
		for (int t = 0; t < Size; t++)
			Elements[t] = NULL;
	}
	CGESlotArray(int size, int growth)
	{
		LastFreedSlot = 0;
		Growth = growth;
		Size = size;
		Elements = new T[Size]();
		for (int t = 0; t < Size; t++)
			Elements[t] = NULL;
	}

	~CGESlotArray()
	{
		SAFE_DELETE(Elements)
	}

	int count() const
	{
		int count = 0;
		for (int t = 0; t < Size; t++)
		{
			if (Elements[t] != NULL)
				count++;
		}
		return count;
	}
	bool add(T element)
	{
		if (LastFreedSlot >= 0)
		{
			Elements[LastFreedSlot] = element;
			if (LastFreedSlot < Size - 1 && Elements[LastFreedSlot + 1] == NULL)	// Optimisation - If next slot is free then set LastFreedSlot as the next slot
				LastFreedSlot++;
			else
				LastFreedSlot = -1;
			return true;
		}
		// find a free slot
		int t;
		for (t = 0; t < Size; t++)
		{
			if (Elements[t] == NULL)
			{
				Elements[t] = element;
				if (t < Size - 1 && Elements[t + 1] == NULL)	// Optimisation - If next slot is free then set LastFreedSlot as the next slot
					LastFreedSlot = t + 1;
				return true;
			}
		}

		// If we are not allowed to grow then return error
		if (Growth == 0)
			return false;

		// No free slots so grow the array
		grow(Growth);
		Elements[t] = element;
		LastFreedSlot = t + 1;

		return true;
	}

	void remove(T element)
	{
		for (int t = 0; t < Size; t++)
		{
			if (Elements[t] == element)
			{
				Elements[t] = NULL;
				LastFreedSlot = t;
				break;
			}
		}
	}

	void remove(int index)
	{
		if (index < 0 || index >= Size)
			return;
		Elements[index] = NULL;
		LastFreedSlot = index;
	}

	T element_at(int index) const
	{
		if (index < 0 || index >= Size)
			return NULL;
		return Elements[index];
	}

	bool set(int index, T element)
	{
		if (index < 0 || index >= Size)
			return false;
		Elements[index] = element;
		if (index == LastFreedSlot)
			LastFreedSlot = -1;

		return true;
	}

	void grow(int growth)
	{
		if (growth <= 0)
			return;
		T* elements = new T[Size + growth]();
		for (int t = 0; t < Size; t++)
			elements[t] = Elements[t];
		for (int t = 0; t < growth; t++)
			elements[t + Size] = NULL;
		delete[] Elements;
		Elements = elements;
		Size += growth;
	}

	void growToSize(int new_size)
	{
		if (new_size <= 0 || new_size <= Size)
			return;
		grow(new_size - Size);
	}

	void resize(int size)
	{
		if (size <= 0 || size == Size)
			return;

		if (size > Size)
			grow(size - Size);
		else
		{
			T* elements = new T[size]();
			for (int t = 0; t < size; t++)
				elements[t] = Elements[t];

			delete Elements;
			Elements = elements;
			Size = size;
			if (LastFreedSlot >= size)
				LastFreedSlot = -1;
		}
	}

	int getLastUsedSlot() const
	{
		for (int t = Size - 1; t >= 0; t--)
		{
			if (Elements[t] != NULL)
				return t;
		}

		return Size - 1;
	}

	void clear(bool delete_elements = false)
	{
		for (int t = 0; t < Size; t++)
		{
			if (delete_elements)
			{
				SAFE_DELETE(Elements[t])
			}
			Elements[t] = NULL;
		}
		LastFreedSlot = 0;
	}
};