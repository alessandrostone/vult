

type template = string -> string -> Pla.t -> Pla.t

type t = template * template

module Default = struct

   let header (_:string) (output:string) (code:Pla.t) : Pla.t =
      let file = String.uppercase output in
      {pla|
#ifndef <#file#s>_H
#define <#file#s>_H
#include <stdint.h>
#include <math.h>
#include "vultin.h"

<#code#>

#endif // <#file#s>_H
|pla}

   let implementation (_:string) (output:string) (code:Pla.t) : Pla.t =
      {pla|
#include "<#output#s>.h"

<#code#>
|pla}

   let get : t = header, implementation

end

let apply (is_header:bool) (template:string) (module_name:string) (output:string) (code:Pla.t) : Pla.t =
   let header,impl =
      match template with
      | "none"    -> Default.get
      | "default" -> Default.get
      | "teensy"  -> TeensyAudio.get
      | t -> failwith (Printf.sprintf "The template '%s' is not available for this generator" t)
   in
   if is_header then
      header module_name output code
   else
      impl module_name output code