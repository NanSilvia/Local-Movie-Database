#pragma once


template <typename TElement = int>
class Dynamic_vector {
	private:
		TElement* elements;
		int capacity;
		int length;
		void resize();
	public:
		Dynamic_vector(int capacity = 10);

		Dynamic_vector(const Dynamic_vector& vector);
		
		~Dynamic_vector();
		
		int get_length() const;

		int get_capacity() const;

		void add_element(TElement element);

		void delete_element(TElement element);

		void update_element(TElement element);

		TElement& operator[](int position);

		Dynamic_vector& operator=(const Dynamic_vector& vector);

		class iterator {
			private:
				TElement* pointer_to_current_element;
			public:
				iterator(TElement* pointer): pointer_to_current_element{ pointer } {}
					
				TElement operator*();
				
				bool operator!=(const iterator& iterator);

				iterator operator++();
				iterator operator++(int);
				

		};

		typename iterator begin();

		typename iterator end();

};


template<typename TElement>
inline void Dynamic_vector<TElement>::resize()
{
	this->capacity *= 2;
	TElement* auxiliar = new TElement[this->capacity];
	for (int index = 0; index < this->length; index++) {
		auxiliar[index] = this->elements[index];
	}
	delete[] this->elements;
	this->elements = auxiliar;
}


template<typename TElement>
inline Dynamic_vector<TElement>::Dynamic_vector(int capacity): capacity{capacity}, length{0}
{
	this->elements = new TElement[this->capacity];
}


template<typename TElement>
inline Dynamic_vector<TElement>::Dynamic_vector(const Dynamic_vector& vector)
{
	this->capacity = vector.capacity;
	this->length = vector.length;
	this->elements = new TElement[this->capacity];
	for (int index = 0; index < this->length; index++)
		this->elements[index] = vector.elements[index];
}


template<typename TElement>
inline Dynamic_vector<TElement>::~Dynamic_vector()
{
	delete[] this->elements;
}


template<typename TElement>
inline int Dynamic_vector<TElement>::get_length() const
{
	return this->length;
}

template<typename TElement>
inline int Dynamic_vector<TElement>::get_capacity() const
{
	return this->capacity;
}


template<typename TElement>
inline void Dynamic_vector<TElement>::add_element(TElement element)
{
	if (this->length == this->capacity)
		this->resize();
	this->elements[this->length++] = element;
}

template<typename TElement>
inline void Dynamic_vector<TElement>::delete_element(TElement element)
{
	for (int index = 0; index < this->length; index++) {
		if (this->elements[index] == element) {
			this->elements[index] = this->elements[--this->length];
		}
	}
}

template<typename TElement>
inline void Dynamic_vector<TElement>::update_element(TElement element)
{
	this->delete_element(element);
	this->add_element(element);

}


template<typename TElement>
inline TElement& Dynamic_vector<TElement>::operator[](int position)
{
	return this->elements[position];
}


template<typename TElement>
inline Dynamic_vector<TElement>& Dynamic_vector<TElement>::operator=(const Dynamic_vector& vector)
{
	if (this == &vector)
		return *this;

	this->capacity = vector.capacity;
	this->length = vector.length;
	
	delete[] this->elements;

	this->elements = new TElement[this->capacity];
	for (int index = 0; index < this->length; index++)
		this->elements[index] = vector.elements[index];
	return *this;
}


template<typename TElement>
inline typename Dynamic_vector<TElement>::iterator Dynamic_vector<TElement>::begin()
{
	return iterator{this->elements};
}


template<typename TElement>
inline typename Dynamic_vector<TElement>::iterator Dynamic_vector<TElement>::end()
{
	return iterator{this->elements + length};
}

template<typename TElement>
inline TElement Dynamic_vector<TElement>::iterator::operator*()
{
	return *this->pointer_to_current_element;
}

template<typename TElement>
inline bool Dynamic_vector<TElement>::iterator::operator!=(const iterator& iterator)
{
	return this->pointer_to_current_element != iterator.pointer_to_current_element;
}

template<typename TElement>
inline typename Dynamic_vector<TElement>::iterator Dynamic_vector<TElement>::iterator::operator++()
{
	this->pointer_to_current_element++;
	return *this;
}

template<typename TElement>
inline typename Dynamic_vector<TElement>::iterator Dynamic_vector<TElement>::iterator::operator++(int)
{
	iterator auxiliar = *this;
	this->pointer_to_current_element++;
	return auxiliar;
}
