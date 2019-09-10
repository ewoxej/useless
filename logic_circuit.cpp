//a simple class for model logic circuits, writing using templates
#include <iostream>
#include <type_traits>

class logic_and;
class logic_or;
class logic_not;
class logic_buffer;

template<class T>
struct LogicElement
{
   template<class Q = T>
   typename std::enable_if<std::is_same<Q, logic_and>::value, bool>::type operator()(bool val1, bool val2)
   {
      return val1 and val2;
   }

   template<class Q = T>
   typename std::enable_if<std::is_same<Q, logic_or>::value, bool>::type operator()( bool val1, bool val2 )
   {
      return val1 or val2;
   }

   template<class Q = T>
   typename std::enable_if<std::is_same<Q, logic_not>::value, bool>::type operator()( bool val1 )
   {
      return !val1;
   }

   template<class Q = T>
   typename std::enable_if<std::is_same<Q, logic_buffer>::value, bool>::type operator()( bool val1 )
   {
      return val1;
   }

};

int main()
{

   LogicElement<logic_not> c_inv;
   LogicElement<logic_and> nc_and_a;
   LogicElement<logic_and> nc_and_b;
   LogicElement<logic_or>  final_or;
   bool input_a = false;
   bool input_b = true;
   bool input_c = true;
   bool output =
      final_or
      (
         nc_and_a
         ( 
            c_inv( input_c ),
            input_a 
         ),
         nc_and_b
         (
            c_inv( input_c ),
            input_b 
         )
      );
   std::cout << output;
   system( "pause" );

   return 0;
}