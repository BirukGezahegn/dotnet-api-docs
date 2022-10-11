﻿module compare22

// <Snippet22>
open System

let s1 = "Ani\u00ADmal"
let s2 = "animal"

printfn $"Comparison of '{s1}' and '{s2}': {String.Compare(s1, s2, true)}"

// The example displays the following output:
//       Comparison of 'Ani-mal' and 'animal': 0
// </Snippet22>