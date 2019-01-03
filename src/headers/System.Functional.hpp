#ifndef _SYSTEM_FUNCTIONAL_HPP
#define _SYSTEM_FUNCTIONAL_HPP
#include <functional>

namespace System {
namespace Functional {
	
	using Action = std::function<void ()>;

	template<typename... TArgs>
	using ActionN = std::function<void (TArgs...)>;

	/*
	 Generator:
	 	public static String repeat(String str, int times) {
			StringBuilder sb = new StringBuilder();
			for(int i = 1; i <= times; i++) {
				if(i != 1)
					sb.append(", ");
				sb.append(str + i);
			}
			return sb.toString();
		}

	 	for(int i = 1; i <=20; i++) {
			System.out.print("template<");
			System.out.print(repeat("typename TArg", i));
			System.out.print("> using Action");
			System.out.print(i);
			System.out.print(" = ActionN<");
			System.out.print(repeat("TArg", i));
			System.out.println(">;");
		} 
	 */
	template<typename TArg1> using Action1 = ActionN<TArg1>;
	template<typename TArg1, typename TArg2> using Action2 = ActionN<TArg1, TArg2>;
	template<typename TArg1, typename TArg2, typename TArg3> using Action3 = ActionN<TArg1, TArg2, TArg3>;
	template<typename TArg1, typename TArg2, typename TArg3, typename TArg4> using Action4 = ActionN<TArg1, TArg2, TArg3, TArg4>;
	template<typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5> using Action5 = ActionN<TArg1, TArg2, TArg3, TArg4, TArg5>;
	template<typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6> using Action6 = ActionN<TArg1, TArg2, TArg3, TArg4, TArg5, TArg6>;
	template<typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7> using Action7 = ActionN<TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7>;
	template<typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8> using Action8 = ActionN<TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8>;
	template<typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8, typename TArg9> using Action9 = ActionN<TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9>;
	template<typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8, typename TArg9, typename TArg10> using Action10 = ActionN<TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10>;
	template<typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8, typename TArg9, typename TArg10, typename TArg11> using Action11 = ActionN<TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11>;
	template<typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8, typename TArg9, typename TArg10, typename TArg11, typename TArg12> using Action12 = ActionN<TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12>;
	template<typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8, typename TArg9, typename TArg10, typename TArg11, typename TArg12, typename TArg13> using Action13 = ActionN<TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13>;
	template<typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8, typename TArg9, typename TArg10, typename TArg11, typename TArg12, typename TArg13, typename TArg14> using Action14 = ActionN<TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14>;
	template<typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8, typename TArg9, typename TArg10, typename TArg11, typename TArg12, typename TArg13, typename TArg14, typename TArg15> using Action15 = ActionN<TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15>;
	template<typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8, typename TArg9, typename TArg10, typename TArg11, typename TArg12, typename TArg13, typename TArg14, typename TArg15, typename TArg16> using Action16 = ActionN<TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16>;
	template<typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8, typename TArg9, typename TArg10, typename TArg11, typename TArg12, typename TArg13, typename TArg14, typename TArg15, typename TArg16, typename TArg17> using Action17 = ActionN<TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17>;
	template<typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8, typename TArg9, typename TArg10, typename TArg11, typename TArg12, typename TArg13, typename TArg14, typename TArg15, typename TArg16, typename TArg17, typename TArg18> using Action18 = ActionN<TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18>;
	template<typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8, typename TArg9, typename TArg10, typename TArg11, typename TArg12, typename TArg13, typename TArg14, typename TArg15, typename TArg16, typename TArg17, typename TArg18, typename TArg19> using Action19 = ActionN<TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19>;
	template<typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8, typename TArg9, typename TArg10, typename TArg11, typename TArg12, typename TArg13, typename TArg14, typename TArg15, typename TArg16, typename TArg17, typename TArg18, typename TArg19, typename TArg20> using Action20 = ActionN<TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19, TArg20>;

	template <typename TArg>
	Action Bind(ActionN<TArg> fn, TArg value){
		return [=](){
			fn(value);
		};
	}

	template <typename TArg, typename... TArgs>
	ActionN<TArgs...> Bind(ActionN<TArg, TArgs...> fn, TArg value){
		return [=](TArgs... rest){
			fn(value, rest...);
		};
	}

	template <typename TResult>
	using Func = std::function<TResult ()>;

	template <typename TResult, typename... TArgs>
	using FuncN = std::function<TResult (TArgs...)>;

	/*
	 Generator:
	 	for(int i = 1; i <=20; i++) {
			System.out.print("template<typename TResult, ");
			System.out.print(repeat("typename TArg", i));
			System.out.print("> using Func");
			System.out.print(i);
			System.out.print(" = FuncN<TResult, ");
			System.out.print(repeat("TArg", i));
			System.out.println(">;");
		}
	 */
	template<typename TResult, typename TArg1> using Func1 = FuncN<TResult, TArg1>;
	template<typename TResult, typename TArg1, typename TArg2> using Func2 = FuncN<TResult, TArg1, TArg2>;
	template<typename TResult, typename TArg1, typename TArg2, typename TArg3> using Func3 = FuncN<TResult, TArg1, TArg2, TArg3>;
	template<typename TResult, typename TArg1, typename TArg2, typename TArg3, typename TArg4> using Func4 = FuncN<TResult, TArg1, TArg2, TArg3, TArg4>;
	template<typename TResult, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5> using Func5 = FuncN<TResult, TArg1, TArg2, TArg3, TArg4, TArg5>;
	template<typename TResult, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6> using Func6 = FuncN<TResult, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6>;
	template<typename TResult, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7> using Func7 = FuncN<TResult, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7>;
	template<typename TResult, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8> using Func8 = FuncN<TResult, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8>;
	template<typename TResult, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8, typename TArg9> using Func9 = FuncN<TResult, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9>;
	template<typename TResult, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8, typename TArg9, typename TArg10> using Func10 = FuncN<TResult, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10>;
	template<typename TResult, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8, typename TArg9, typename TArg10, typename TArg11> using Func11 = FuncN<TResult, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11>;
	template<typename TResult, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8, typename TArg9, typename TArg10, typename TArg11, typename TArg12> using Func12 = FuncN<TResult, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12>;
	template<typename TResult, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8, typename TArg9, typename TArg10, typename TArg11, typename TArg12, typename TArg13> using Func13 = FuncN<TResult, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13>;
	template<typename TResult, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8, typename TArg9, typename TArg10, typename TArg11, typename TArg12, typename TArg13, typename TArg14> using Func14 = FuncN<TResult, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14>;
	template<typename TResult, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8, typename TArg9, typename TArg10, typename TArg11, typename TArg12, typename TArg13, typename TArg14, typename TArg15> using Func15 = FuncN<TResult, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15>;
	template<typename TResult, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8, typename TArg9, typename TArg10, typename TArg11, typename TArg12, typename TArg13, typename TArg14, typename TArg15, typename TArg16> using Func16 = FuncN<TResult, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16>;
	template<typename TResult, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8, typename TArg9, typename TArg10, typename TArg11, typename TArg12, typename TArg13, typename TArg14, typename TArg15, typename TArg16, typename TArg17> using Func17 = FuncN<TResult, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17>;
	template<typename TResult, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8, typename TArg9, typename TArg10, typename TArg11, typename TArg12, typename TArg13, typename TArg14, typename TArg15, typename TArg16, typename TArg17, typename TArg18> using Func18 = FuncN<TResult, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18>;
	template<typename TResult, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8, typename TArg9, typename TArg10, typename TArg11, typename TArg12, typename TArg13, typename TArg14, typename TArg15, typename TArg16, typename TArg17, typename TArg18, typename TArg19> using Func19 = FuncN<TResult, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19>;
	template<typename TResult, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8, typename TArg9, typename TArg10, typename TArg11, typename TArg12, typename TArg13, typename TArg14, typename TArg15, typename TArg16, typename TArg17, typename TArg18, typename TArg19, typename TArg20> using Func20 = FuncN<TResult, TArg1, TArg2, TArg3, TArg4, TArg5, TArg6, TArg7, TArg8, TArg9, TArg10, TArg11, TArg12, TArg13, TArg14, TArg15, TArg16, TArg17, TArg18, TArg19, TArg20>;

	template <typename TResult, typename TArg>
	Func<TResult> Bind(FuncN<TResult, TArg> fn, TArg value){
		return [=](){
			return fn(value);
		};
	}

	template <typename TResult, typename TArg, typename... TArgs>
	FuncN<TResult, TArgs...> Bind(FuncN<TResult, TArg, TArgs...> fn, TArg value){
		return [=](TArgs... rest){
			return fn(value, rest...);
		};
	}
	//Extra (convenience names)
	/**
	 * Represents a function that checks if a condition holds for a particular input value.
	 */
	template<typename T> using Predicate = FuncN<bool, T>;
	/**
	 * Represents a function that returns a value without any inputs. Usually used for generating values.
	 */
	template<typename T> using Supplier = FuncN<T>;
	/**
	 * Represents an ActionN that takes in a value and operates on it without returning anything.
	 */
	template<typename T> using Consumer = ActionN<T>;
	/**
	 * Represents a unitary operator
	 */
	template<typename IN, typename OUT> using UnaryOperator = FuncN<OUT,IN>;
	/**
	 * Represents a binary operator
	 */
	template<typename IN1, typename IN2, typename OUT> using BinaryOperator = FuncN<OUT,IN1,IN2>;
}
}

#endif