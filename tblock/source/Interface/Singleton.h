#ifndef _SINGLETON_H_
#define _SINGLETON_H_

template <class T>
class Singleton
{
	private:
		static T* _self;
		static int _refcount;

	protected:
		Singleton() {}
		virtual ~Singleton()
		{
			_self = 0;
		}

	public:
		static T* GetInstance();
		void FreeInstance();
};

template <class T>
T* Singleton<T>::_self = 0;

template <class T>
int Singleton<T>::_refcount = 0;

template <class T>
T* Singleton<T>::GetInstance()
{
  if( !_self )
  {
	  _self = new T;
  }
  
  _refcount++;

  return _self;
}

template <class T>
void Singleton<T>::FreeInstance()
{
  if( --_refcount == 0 )
  {
	  delete this;
  }
}

#endif