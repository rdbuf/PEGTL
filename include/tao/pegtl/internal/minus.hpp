// Copyright (c) 2016-2018 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/PEGTL/

#ifndef TAO_PEGTL_INTERNAL_MINUS_HPP
#define TAO_PEGTL_INTERNAL_MINUS_HPP

#include "../config.hpp"

#include "skip_control.hpp"

#include "../apply_mode.hpp"
#include "../memory_input.hpp"
#include "../rewind_mode.hpp"

namespace tao
{
   namespace TAO_PEGTL_NAMESPACE
   {
      namespace internal
      {
         [[nodiscard]] inline const char* source_pointer( const char* source ) noexcept
         {
            return source;
         }

         [[nodiscard]] inline const char* source_pointer( const std::string& source ) noexcept
         {
            return source.c_str();
         }

         template< typename R, typename S >
         struct minus
         {
            using analyze_t = typename R::analyze_t;  // NOTE: S is currently ignored for analyze().

            template< apply_mode A,
                      rewind_mode,
                      template< typename... >
                      class Action,
                      template< typename... >
                      class Control,
                      typename Input,
                      typename... States >
            [[nodiscard]] static bool match( Input& in, States&&... st )
            {
               auto m = in.template mark< rewind_mode::required >();

               if( !Control< R >::template match< A, rewind_mode::active, Action, Control >( in, st... ) ) {
                  return false;
               }
               memory_input< tracking_mode::lazy, typename Input::eol_t, const char* > i2( m.iterator(), in.current(), source_pointer( in.source() ) );

               if( !Control< S >::template match< apply_mode::nothing, rewind_mode::active, Action, Control >( i2, st... ) ) {
                  return m( true );
               }
               return m( !i2.empty() );
            }
         };

         template< typename R, typename S >
         inline constexpr bool skip_control< minus< R, S > > = true;

      }  // namespace internal

   }  // namespace TAO_PEGTL_NAMESPACE

}  // namespace tao

#endif
