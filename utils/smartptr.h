#ifndef smartPTR_H
#define smartPTR_H

template<typename T>
class smartptr{
	public:

		//Constructors
		smartptr(T* p):copies(new int(1)), ptr(p)
		{}
		smartptr(const smartptr<T>& cp):copies(cp.copies), ptr(cp.ptr)
		{
			++(*copies);
		}
		//Operators
		smartptr& operator=(const smartptr<T>& cp){
			handle_destruction();
			copies = cp.copies;
			++(*copies);
			ptr = cp.ptr;
			return *this;
		}

		T& operator*() const{
			return *ptr;
		}

		T* operator->() const{
			return ptr;
		}
		//Functions
		operator bool(){
			return ptr;
		}

		int instances(){
			return *copies;
		}

		~smartptr(){
			handle_destruction();
		}

	private:
		int* copies;
		T* ptr;

		void handle_destruction(){
			if(--(*copies) == 0){
				delete ptr;
				delete copies;
			}
		}
	};
#endif
