#pragma once


namespace CommonUtilities
{
	template <class T>
	class BSTSet
	{
	public:
		BSTSet();
		~BSTSet();
		//Returnerar true om elementet finns i m�ngden, och false annars.
		bool HasElement(const T& aValue);
		//Stoppar in elementet i m�ngden, om det inte redan finns d�r. G�r
		//ingenting annars.
		void Insert(const T& aValue);
		//Plockar bort elementet ur m�ngden, om det finns. G�r ingenting annars.
		void Remove(const T& aValue);
	};
}