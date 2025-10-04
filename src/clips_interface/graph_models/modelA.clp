
(defrule rule0
(TripleTemplate (subject  ?rifmember ) (predicate  <http://www.w3.org/2007/rif#class> ) (object  ?rifclass ))
(TripleTemplate (subject  ?rifclass ) (predicate  <http://example.com/as-constraint> ) (object  ?constraintclass ))
(TripleTemplate (subject  ?rifmember ) (predicate  <http://www.w3.org/2007/rif#instance> ) (object  ?rifinstance ))
(TripleTemplate (subject  ?rifinstance ) (predicate  <http://example.com/as-constraint> ) (object  ?constraintinstance ))
(Member (class  <http://white.gobo/modelA#MemberPatternGenerator> ) (instance  ?rifmember ))
(not
(exists
(TripleTemplate (subject  ?rifmember ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?x ))
)
)
	=>
 (bind ?slotinstance   (<http://white.gobo/new-blanknode>) ) (bind ?pattern   (<http://white.gobo/new-blanknode>) ) (bind ?slotclass   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifmember ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?pattern )))(assert(Member (instance  ?pattern ) (class  <http://clips.script/TemplatePatternCE> )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/deftemplate-name> ) (object  "Member" )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/slot> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?slotclass   ?slotinstance  ))))(assert(TripleTemplate (subject  ?slotclass ) (predicate  <http://clips.script/slot-name> ) (object  "class" )))(assert(TripleTemplate (subject  ?slotclass ) (predicate  <http://clips.script/constraint> ) (object  ?constraintclass )))(assert(TripleTemplate (subject  ?slotinstance ) (predicate  <http://clips.script/slot-name> ) (object  "instance" )))(assert(TripleTemplate (subject  ?slotinstance ) (predicate  <http://clips.script/constraint> ) (object  ?constraintinstance ))))

(defrule rule1 (declare (salience -1))
(TripleTemplate (subject  ?defrule ) (predicate  <http://example.com/bound-variable> ) (object  ?listasvar ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/add-as-pattern> ) (object  ?defrule ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/as-constraint> ) (object  ?listasvar ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/as-lhs-pattern> ) (object  ?pattern ))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?riflist ))
(not
(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/used-as-pattern-in> ) (object  ?defrule ))
)
(not
(exists
(and
(TripleTemplate (subject  ?pattern ) (predicate  <http://example.com/needs-variable> ) (object  ?x ))
(not
(TripleTemplate (subject  ?defrule ) (predicate  <http://example.com/bound-variable> ) (object  ?x ))
)
)
)
)
	=>
 (bind ?assignpattern   (<http://white.gobo/new-blanknode>) ) (bind ?testvarpattern   (<http://white.gobo/new-blanknode>) ) (bind ?testvaraction   (<http://white.gobo/new-blanknode>) ) (bind ?tmplistasvar   (<http://white.gobo/new-blanknode>) ) (bind ?oldpatternlist   (do-for-fact (( ?fcct3 TripleTemplate)) (and (eq ?fcct3:subject   ?defrule  )  (eq ?fcct3:predicate   <http://clips.script/conditional-element>  ) ) (fact-slot-value ?fcct3   object  ) )  )(assert(Member (instance  ?tmplistasvar ) (class  <http://clips.script/Variable> )))(assert(Member (instance  ?tmplistasvar ) (class  <http://example.com/Variable> )))(assert(Member (instance  ?testvarpattern ) (class  <http://clips.script/TestCE> )))(assert(TripleTemplate (subject  ?testvarpattern ) (predicate  <http://clips.script/function-call> ) (object  ?testvaraction )))(assert(TripleTemplate (subject  ?testvaraction ) (predicate  <http://clips.script/function-name> ) (object  "eq" )))(assert(TripleTemplate (subject  ?testvaraction ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?listasvar   ?tmplistasvar  ))))(assert(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/used-as-pattern-in> ) (object  ?defrule )))(assert(Member (instance  ?assignpattern ) (class  <http://clips.script/AssignedPatternCE> )))(assert(TripleTemplate (subject  ?assignpattern ) (predicate  <http://clips.script/pattern-ce> ) (object  ?pattern )))(assert(TripleTemplate (subject  ?assignpattern ) (predicate  <http://clips.script/fact-var-symbol> ) (object  ?tmplistasvar ))) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?defrule  )  (eq ?fct1:predicate   <http://clips.script/conditional-element>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?defrule ) (predicate  <http://clips.script/conditional-element> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?oldpatternlist   ?assignpattern   ?testvarpattern  ))))(assert(TripleTemplate (subject  ?defrule ) (predicate  <http://example.com/transfer-bound-variables-from> ) (object  ?pattern ))))

(defrule rule2 (declare (salience -101))
(TripleTemplate (subject  ?rif ) (predicate  <http://white.gobo/local/b/ncfe8f320_n11750#add-args-as-expression-from> ) (object  ?arglist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#numeric-greater-than> (<http://www.w3.org/2007/rif-builtin-function#count> ?arglist  )  "0^^http://www.w3.org/2001/XMLSchema#integer"  ))

	=>
(assert(Member (instance  ?rif ) (class  <http://example.com/couldnt-add-all-items> ))) (<http://white.gobo/set-graph-in-errorstate> "Missing%20items%20for%20list%28ex%3Acouldnt-add-all-items%29"  ))

(defrule rule3 (declare (salience 10))
(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/add-as-pattern> ) (object  ?defrule ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://white.gobo/modelA#binds-variable> ) (object  ?clipsrestvar ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://www.w3.org/2007/rif#rest> ) (object  ?rest ))
(TripleTemplate (subject  ?rest ) (predicate  <http://example.com/as-expression> ) (object  ?clipsrestvar ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rest ))
(Atom (op  <http://white.gobo/local/b/ncfe8f320_n11750#combine-multifield-as-list> ) (args  ?rest  ?multifieldvar ))
(not
(TripleTemplate (subject  ?defrule ) (predicate  <http://example.com/bound-variable> ) (object  ?clipsrestvar ))
)
	=>
 (bind ?function   (<http://white.gobo/new-blanknode>) ) (bind ?expand   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?clipsrestvar ) (predicate  <http://clips.script/var-as-const-expr> ) (object  ?function )))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-name> ) (object  "%3Chttp%3A%2F%2Fwww.w3.org%2F2007%2Frif-builtin-function%23make-list%3E" )))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?expand  ))))(assert(TripleTemplate (subject  ?expand ) (predicate  <http://clips.script/function-name> ) (object  "expand%24" )))(assert(TripleTemplate (subject  ?expand ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?multifieldvar  )))))

(defrule rule4 (declare (salience -1))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?riflist ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/as-lhs-pattern> ) (object  ?pattern ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/as-constraint> ) (object  ?listasvar ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/add-as-pattern> ) (object  ?defrule ))
(not
(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/used-as-pattern-in> ) (object  ?defrule ))
)
(not
(TripleTemplate (subject  ?defrule ) (predicate  <http://example.com/bound-variable> ) (object  ?listasvar ))
)
(not
(exists
(and
(TripleTemplate (subject  ?pattern ) (predicate  <http://example.com/needs-variable> ) (object  ?x ))
(not
(TripleTemplate (subject  ?defrule ) (predicate  <http://example.com/bound-variable> ) (object  ?x ))
)
)
)
)
	=>
 (bind ?assignpattern   (<http://white.gobo/new-blanknode>) ) (bind ?oldpatternlist   (do-for-fact (( ?fcct2 TripleTemplate)) (and (eq ?fcct2:subject   ?defrule  )  (eq ?fcct2:predicate   <http://clips.script/conditional-element>  ) ) (fact-slot-value ?fcct2   object  ) )  )(assert(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/used-as-pattern-in> ) (object  ?defrule )))(assert(Member (instance  ?assignpattern ) (class  <http://clips.script/AssignedPatternCE> )))(assert(TripleTemplate (subject  ?assignpattern ) (predicate  <http://clips.script/pattern-ce> ) (object  ?pattern )))(assert(TripleTemplate (subject  ?assignpattern ) (predicate  <http://clips.script/fact-var-symbol> ) (object  ?listasvar ))) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?defrule  )  (eq ?fct1:predicate   <http://clips.script/conditional-element>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?defrule ) (predicate  <http://clips.script/conditional-element> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?oldpatternlist   ?assignpattern  ))))(assert(TripleTemplate (subject  ?defrule ) (predicate  <http://example.com/transfer-bound-variables-from> ) (object  ?pattern ))))

(defrule rule5 (declare (salience 10))
(Member (class  <http://white.gobo/modelA#ConstraintGenerator> ) (instance  ?riflist ))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?riflist ))
	=>
 (bind ?listasvar   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/as-constraint> ) (object  ?listasvar )))(assert(Member (instance  ?listasvar ) (class  <http://clips.script/Variable> )))(assert(Member (instance  ?listasvar ) (class  <http://example.com/Variable> )))(assert(Member (instance  ?riflist ) (class  <http://white.gobo/modelA#ConstraintNeedsAdditionalPatterns> ))))

(defrule rule6 (declare (salience 10))
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#pattern-uses-constraint> ) (object  ?riflist ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://www.w3.org/2007/rif#items> ) (object  ?itemlist ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/as-constraint> ) (object  ?listvar ))
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#bound-variable> ) (object  ?assign ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-constraint> ) (object  ?assign ))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?riflist ))
(Member (class  <http://white.gobo/modelA#ConstraintGenerator> ) (instance  ?riflist ))
(Atom (op  <http://white.gobo/local/b/ncfe8f320_n11750#always-wrong> ) (args ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?itemlist   ?rifvar  ))

	=>
 (bind ?eq   (<http://white.gobo/new-blanknode>) ) (bind ?function   (<http://white.gobo/new-blanknode>) ) (bind ?testpattern   (<http://white.gobo/new-blanknode>) ) (bind ?position   (<http://white.gobo/new-blanknode>) )(assert(Member (instance  ?testpattern ) (class  <http://clips.script/TestCE> )))(assert(TripleTemplate (subject  ?testpattern ) (predicate  <http://clips.script/function-call> ) (object  ?eq )))(assert(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#lhs-pattern-after-conditions> ) (object  ?testpattern )))(assert(TripleTemplate (subject  ?eq ) (predicate  <http://clips.script/function-name> ) (object  "eq" )))(assert(TripleTemplate (subject  ?eq ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?assign   ?function  ))))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-name> ) (object  "%3Chttp%3A%2F%2Fwww.w3.org%2F2007%2Frif-builtin-function%23get%3E" )))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?listvar   ?position  ))))(assert(TripleTemplate (subject  ?position ) (predicate  <http://clips.script/string> ) (object  (<http://white.gobo/literal-to-clipsconstant> (<http://www.w3.org/2007/rif-builtin-function#get> (<http://www.w3.org/2007/rif-builtin-function#index-of> ?itemlist   ?rifvar  )  "0^^http://www.w3.org/2001/XMLSchema#integer"  ) )))))

(defrule rule7 (declare (salience 10))
(Member (class  <http://white.gobo/modelA#ExpressionGenerator> ) (instance  ?riflist ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://www.w3.org/2007/rif#items> ) (object  ?itemlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?itemlist  ))

(not
(exists
(TripleTemplate (subject  ?riflist ) (predicate  <http://www.w3.org/2007/rif#rest> ) (object  ?rest ))
)
)
	=>
 (bind ?function   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/as-expression> ) (object  ?function )))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-name> ) (object  "%3Chttp%3A%2F%2Fwww.w3.org%2F2007%2Frif-builtin-function%23make-list%3E" )))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>))))(assert(TripleTemplate (subject  ?function ) (predicate  <http://white.gobo/local/b/ncfe8f320_n11750#add-args-as-expression-from> ) (object  ?itemlist ))))

(defrule rule8 (declare (salience 10))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?riflist ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/as-constraint> ) (object  ?listvar ))
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#pattern-uses-constraint> ) (object  ?riflist ))
(TripleTemplate (subject  ?rest ) (predicate  <http://example.com/as-constraint> ) (object  ?assign ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://www.w3.org/2007/rif#rest> ) (object  ?rest ))
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#bound-variable> ) (object  ?assign ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://www.w3.org/2007/rif#items> ) (object  ?itemlist ))
(Member (class  <http://white.gobo/modelA#ConstraintGenerator> ) (instance  ?riflist ))
	=>
 (bind ?testpattern   (<http://white.gobo/new-blanknode>) ) (bind ?position   (<http://white.gobo/new-blanknode>) ) (bind ?eq   (<http://white.gobo/new-blanknode>) ) (bind ?function   (<http://white.gobo/new-blanknode>) )(assert(Member (instance  ?testpattern ) (class  <http://clips.script/TestCE> )))(assert(TripleTemplate (subject  ?testpattern ) (predicate  <http://clips.script/function-call> ) (object  ?eq )))(assert(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#lhs-pattern-after-conditions> ) (object  ?testpattern )))(assert(TripleTemplate (subject  ?eq ) (predicate  <http://clips.script/function-name> ) (object  "eq" )))(assert(TripleTemplate (subject  ?eq ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?assign   ?function  ))))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-name> ) (object  "%3Chttp%3A%2F%2Fwww.w3.org%2F2007%2Frif-builtin-function%23sublist%3E" )))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?listvar   ?position  ))))(assert(TripleTemplate (subject  ?position ) (predicate  <http://clips.script/string> ) (object  (<http://white.gobo/literal-to-clipsconstant> (<http://www.w3.org/2007/rif-builtin-function#count> ?itemlist  ) )))))

(defrule rule9 (declare (salience 10))
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#pattern-uses-constraint> ) (object  ?riflist ))
(TripleTemplate (subject  ?rest ) (predicate  <http://example.com/as-constraint> ) (object  ?assign ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://www.w3.org/2007/rif#items> ) (object  ?itemlist ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/as-constraint> ) (object  ?listvar ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://www.w3.org/2007/rif#rest> ) (object  ?rest ))
(Member (class  <http://white.gobo/modelA#ConstraintGenerator> ) (instance  ?riflist ))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?riflist ))
(Member (class  <http://white.gobo/modelA#ListAsConstraint> ) (instance  ?riflist ))
(Atom (op  <http://white.gobo/local/b/ncfe8f320_n11750#always-wrong> ) (args ))
(not
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#bound-variable> ) (object  ?assign ))
)
	=>
 (bind ?function   (<http://white.gobo/new-blanknode>) ) (bind ?position   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?assign ) (predicate  <http://clips.script/var-as-const-expr> ) (object  ?function )))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-name> ) (object  "%3Chttp%3A%2F%2Fwww.w3.org%2F2007%2Frif-builtin-function%23sublist%3E" )))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?listvar   ?position  ))))(assert(TripleTemplate (subject  ?position ) (predicate  <http://clips.script/string> ) (object  (<http://white.gobo/literal-to-clipsconstant> (<http://www.w3.org/2007/rif-builtin-function#count> ?itemlist  ) )))))

(defrule rule10 (declare (salience 10))
(TripleTemplate (subject  ?firstarg ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsconstraint ))
(TripleTemplate (subject  ?slotitems ) (predicate  <http://clips.script/constraints> ) (object  ?listconstraints ))
(TripleTemplate (subject  ?slotitems ) (predicate  <http://white.gobo/local/b/ncfe8f320_n11750#add-args-as-constraints-from> ) (object  ?itemlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?itemlist  ))

(test (<http://www.w3.org/2007/rif-builtin-predicate#numeric-greater-than> (<http://www.w3.org/2007/rif-builtin-function#count> ?itemlist  )  "0^^http://www.w3.org/2001/XMLSchema#integer"  ))

(test (eq ?firstarg   (<http://www.w3.org/2007/rif-builtin-function#get> ?itemlist   "0^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

	=>
 (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?slotitems  )  (eq ?fct1:predicate   <http://clips.script/constraints>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?slotitems ) (predicate  <http://clips.script/constraints> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?listconstraints   ?clipsconstraint  )))) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?slotitems  )  (eq ?fct1:predicate   <http://white.gobo/local/b/ncfe8f320_n11750#add-args-as-constraints-from>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?slotitems ) (predicate  <http://white.gobo/local/b/ncfe8f320_n11750#add-args-as-constraints-from> ) (object  (<http://www.w3.org/2007/rif-builtin-function#remove> ?itemlist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )))))

(defrule rule11 (declare (salience 10))
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#pattern-uses-constraint> ) (object  ?riflist ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/as-constraint> ) (object  ?listvar ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-constraint> ) (object  ?assign ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://www.w3.org/2007/rif#items> ) (object  ?itemlist ))
(Member (class  <http://white.gobo/modelA#ConstraintGenerator> ) (instance  ?riflist ))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?riflist ))
(Atom (op  <http://white.gobo/local/b/ncfe8f320_n11750#always-wrong> ) (args ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?itemlist   ?rifvar  ))

(not
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#bound-variable> ) (object  ?assign ))
)
	=>
 (bind ?position   (<http://white.gobo/new-blanknode>) ) (bind ?function   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?assign ) (predicate  <http://clips.script/var-as-const-expr> ) (object  ?function )))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-name> ) (object  "%3Chttp%3A%2F%2Fwww.w3.org%2F2007%2Frif-builtin-function%23get%3E" )))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?listvar   ?position  ))))(assert(TripleTemplate (subject  ?position ) (predicate  <http://clips.script/string> ) (object  (<http://white.gobo/literal-to-clipsconstant> (<http://www.w3.org/2007/rif-builtin-function#get> (<http://www.w3.org/2007/rif-builtin-function#index-of> ?itemlist   ?rifvar  )  "0^^http://www.w3.org/2001/XMLSchema#integer"  ) )))))

(defrule rule12 (declare (salience 10))
(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-args> ) (object  ?currentexprlist ))
(TripleTemplate (subject  ?function ) (predicate  <http://white.gobo/local/b/ncfe8f320_n11750#add-args-as-expression-from> ) (object  ?itemlist ))
(TripleTemplate (subject  ?firstarg ) (predicate  <http://example.com/as-expression> ) (object  ?firstasexpression ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#numeric-greater-than> (<http://www.w3.org/2007/rif-builtin-function#count> ?itemlist  )  "0^^http://www.w3.org/2001/XMLSchema#integer"  ))

(test (eq ?firstarg   (<http://www.w3.org/2007/rif-builtin-function#get> ?itemlist   "0^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

	=>
 (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?function  )  (eq ?fct1:predicate   <http://clips.script/function-args>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?currentexprlist   ?firstasexpression  )))) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?function  )  (eq ?fct1:predicate   <http://white.gobo/local/b/ncfe8f320_n11750#add-args-as-expression-from>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?function ) (predicate  <http://white.gobo/local/b/ncfe8f320_n11750#add-args-as-expression-from> ) (object  (<http://www.w3.org/2007/rif-builtin-function#remove> ?itemlist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )))))

(defrule rule13 (declare (salience 10))
(TripleTemplate (subject  ?function ) (predicate  <http://white.gobo/local/b/ncfe8f320_n11750#add-args-as-expression-from> ) (object  ?itemlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?itemlist  ))

(test (eq "0^^http://www.w3.org/2001/XMLSchema#integer"   (<http://www.w3.org/2007/rif-builtin-function#count> ?itemlist  ) ))

	=>
 (retract(assert(TripleTemplate (subject  ?function ) (predicate  <http://white.gobo/local/b/ncfe8f320_n11750#add-args-as-expression-from> ) (object  ?itemlist ))) ))

(defrule rule14 (declare (salience 10))
(TripleTemplate (subject  ?riflist ) (predicate  <http://www.w3.org/2007/rif#rest> ) (object  ?rest ))
(not
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rest ))
)
	=>
 (<http://white.gobo/set-graph-in-errorstate> "rif%3Arest%20is%20only%20implemented%20for%20domain%20of%20type%20rif%3AVar"  ))

(defrule rule15 (declare (salience 50))
(TripleTemplate (subject  ?frameobject ) (predicate  <http://example.com/as-constraint> ) (object  ?constraintsubject ))
(TripleTemplate (subject  ?slotvalue ) (predicate  <http://example.com/as-constraint> ) (object  ?constraintobject ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?frameobject ))
(TripleTemplate (subject  ?slotkey ) (predicate  <http://www.w3.org/2007/rif#constIRI> ) (object  "http%3A%2F%2Fwww.w3.org%2F1999%2F02%2F22-rdf-syntax-ns%23type^^http://www.w3.org/2001/XMLSchema#anyURI" ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?slotvalue ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?slotkey ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://example.com/add-as-pattern> ) (object  ?defrule ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?slotlist  ))

(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

(not
(TripleTemplate (subject  ?slot ) (predicate  <http://example.com/used-as-pattern-in> ) (object  ?defrule ))
)
(not
(exists
(and
(TripleTemplate (subject  ?constraintsubject ) (predicate  <http://example.com/needs-variable> ) (object  ?x ))
(not
(TripleTemplate (subject  ?defrule ) (predicate  <http://example.com/bound-variable> ) (object  ?x ))
)
)
)
)
(not
(exists
(and
(TripleTemplate (subject  ?constraintobject ) (predicate  <http://example.com/needs-variable> ) (object  ?z ))
(not
(TripleTemplate (subject  ?defrule ) (predicate  <http://example.com/bound-variable> ) (object  ?z ))
)
)
)
)
	=>
 (bind ?pattern   (<http://white.gobo/new-blanknode>) ) (bind ?slotcls   (<http://white.gobo/new-blanknode>) ) (bind ?slotinstance   (<http://white.gobo/new-blanknode>) ) (bind ?oldpatternlist   (do-for-fact (( ?fcct4 TripleTemplate)) (and (eq ?fcct4:subject   ?defrule  )  (eq ?fcct4:predicate   <http://clips.script/conditional-element>  ) ) (fact-slot-value ?fcct4   object  ) )  )(assert(TripleTemplate (subject  ?slot ) (predicate  <http://example.com/used-as-pattern-in> ) (object  ?defrule )))(assert(TripleTemplate (subject  ?rifframe ) (predicate  <http://example.com/used-as-pattern-in> ) (object  ?defrule )))(assert(Member (instance  ?pattern ) (class  <http://clips.script/TemplatePatternCE> )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/deftemplate-name> ) (object  "Member" )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/slot> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?slotinstance   ?slotcls  ))))(assert(TripleTemplate (subject  ?slotinstance ) (predicate  <http://clips.script/slot-name> ) (object  "instance" )))(assert(TripleTemplate (subject  ?slotinstance ) (predicate  <http://clips.script/constraint> ) (object  ?constraintsubject )))(assert(TripleTemplate (subject  ?slotcls ) (predicate  <http://clips.script/slot-name> ) (object  "class" )))(assert(TripleTemplate (subject  ?slotcls ) (predicate  <http://clips.script/constraint> ) (object  ?constraintobject ))) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?defrule  )  (eq ?fct1:predicate   <http://clips.script/conditional-element>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?defrule ) (predicate  <http://clips.script/conditional-element> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?oldpatternlist   ?pattern  ))))(assert(TripleTemplate (subject  ?defrule ) (predicate  <http://example.com/transfer-bound-variables-from> ) (object  ?constraintsubject )))(assert(TripleTemplate (subject  ?defrule ) (predicate  <http://example.com/transfer-bound-variables-from> ) (object  ?constraintobject ))))

(defrule rule16 (declare (salience -1))
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?rifconstiristring ))
(TripleTemplate (subject  ?targetiri ) (predicate  <http://example.com/as-expression> ) (object  ?clipsvar ))
(TripleTemplate (subject  ?rifexternal ) (predicate  <http://www.w3.org/2007/rif#content> ) (object  ?rifatom ))
(TripleTemplate (subject  ?rifconstiristring ) (predicate  <http://www.w3.org/2007/rif#constIRI> ) (object  "http%3A%2F%2Fwww.w3.org%2F2007%2Frif-builtin-predicate%23iri-string^^http://www.w3.org/2001/XMLSchema#anyURI" ))
(TripleTemplate (subject  ?rifexternal ) (predicate  <http://example.com/add-as-pattern> ) (object  ?defrule ))
(TripleTemplate (subject  ?targetiri ) (predicate  <http://www.w3.org/2007/rif#varname> ) (object  ?varname ))
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
(TripleTemplate (subject  ?targetstring ) (predicate  <http://example.com/as-expression> ) (object  ?clipsexpression ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?rifexternal ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?arglist  ))

(test (eq ?targetiri   (<http://www.w3.org/2007/rif-builtin-function#get> ?arglist   "0^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

(test (eq ?targetstring   (<http://www.w3.org/2007/rif-builtin-function#get> ?arglist   "1^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

(not
(TripleTemplate (subject  ?rifexternal ) (predicate  <http://example.com/used-as-pattern-in> ) (object  ?defrule ))
)
(not
(and
(exists
(TripleTemplate (subject  ?clipsexpression ) (predicate  <http://clips.script/variable-name> ) (object  ?tmp ))
)
(not
(TripleTemplate (subject  ?defrule ) (predicate  <http://example.com/bound-variable> ) (object  ?clipsexpression ))
)
)
)
(not
(TripleTemplate (subject  ?defrule ) (predicate  <http://example.com/bound-variable> ) (object  ?clipsvar ))
)
(not
(exists
(and
(TripleTemplate (subject  ?clipsexpression ) (predicate  <http://example.com/needs-variable> ) (object  ?x ))
(not
(TripleTemplate (subject  ?defrule ) (predicate  <http://example.com/bound-variable> ) (object  ?x ))
)
)
)
)
	=>
(assert(TripleTemplate (subject  ?rifexternal ) (predicate  <http://example.com/used-as-pattern-in> ) (object  ?defrule )))(assert(TripleTemplate (subject  ?clipsvar ) (predicate  <http://clips.script/var-as-const-expr> ) (object  ?clipsexpression ))))

(defrule rule17 (declare (salience 10))
(TripleTemplate (subject  ?rifrule ) (predicate  <http://example.com/add-rule-info> ) (object  ?defrule ))
(TripleTemplate (subject  ?rifrule ) (predicate  <http://www.w3.org/2007/rif#if> ) (object  ?rifcondition ))
	=>
(assert(TripleTemplate (subject  ?rifcondition ) (predicate  <http://example.com/add-as-pattern> ) (object  ?defrule ))))

(defrule rule18 (declare (salience 10))
(Member (class  <http://clips.script/Defrule> ) (instance  ?defrule ))
(TripleTemplate (subject  ?rifcondition ) (predicate  <http://example.com/add-as-pattern> ) (object  ?defrule ))
(TripleTemplate (subject  ?rifcondition ) (predicate  <http://www.w3.org/2007/rif#formulas> ) (object  ?formulalist ))
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?rifcondition ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?formulalist  ))

(or
(Member (class  <http://www.w3.org/2007/rif#SubClass> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#INeg> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#Or> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#Equal> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#Exists> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?formula ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?formulalist   ?formula  ))

	=>
(assert(TripleTemplate (subject  ?formula ) (predicate  <http://example.com/add-as-pattern> ) (object  ?defrule )))(assert(TripleTemplate (subject  ?rifcondition ) (predicate  <http://example.com/used-as-pattern-in> ) (object  ?defrule ))))

(defrule rule19 (declare (salience 10))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://example.com/add-as-pattern> ) (object  ?defrule ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?rifterm ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

	=>
(assert(Member (instance  ?rifterm ) (class  <http://example.com/ConstraintGenerator> ))))

(defrule rule20 (declare (salience 10))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://example.com/add-as-pattern> ) (object  ?defrule ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?constraintlist ))
(or
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifterm ))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?rifterm ))
(Member (class  <http://www.w3.org/2007/rif#Const> ) (instance  ?rifterm ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?rifterm ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?constraintlist   ?rifterm  ))

	=>
(assert(Member (instance  ?rifterm ) (class  <http://example.com/ConstraintGenerator> ))))

(defrule rule21 (declare (salience 10))
(Member (class  <http://www.w3.org/2007/rif#Group> ) (instance  ?subgroup ))
(TripleTemplate (subject  ?supergroup ) (predicate  <http://white.gobo/local/b/ncfe8f320_n10352#priority> ) (object  ?priority ))
(TripleTemplate (subject  ?supergroup ) (predicate  <http://www.w3.org/2007/rif#sentences> ) (object  ?sentences ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?sentences   ?subgroup  ))

(not
(exists
(and
(TripleTemplate (subject  ?subgroup ) (predicate  <http://www.w3.org/2007/rif#behavior> ) (object  ?behavior ))
(TripleTemplate (subject  ?behavior ) (predicate  <http://www.w3.org/2007/rif#Priority> ) (object  ?x ))
)
)
)
	=>
(assert(TripleTemplate (subject  ?subgroup ) (predicate  <http://white.gobo/local/b/ncfe8f320_n10352#priority> ) (object  ?priority ))))

(defrule rule22 (declare (salience 10))
(TripleTemplate (subject  ?rifrule ) (predicate  <http://www.w3.org/2007/rif#then> ) (object  ?rifclause ))
(TripleTemplate (subject  ?rifrule ) (predicate  <http://example.com/add-rule-info> ) (object  ?defrule ))
(Member (class  <http://www.w3.org/2007/rif#Implies> ) (instance  ?rifclause ))
	=>
(assert(TripleTemplate (subject  ?rifclause ) (predicate  <http://example.com/add-rule-info> ) (object  ?defrule ))))

(defrule rule23 (declare (salience 10))
(TripleTemplate (subject  ?rifgroup ) (predicate  <http://white.gobo/local/b/ncfe8f320_n10352#priority> ) (object  ?priority ))
(TripleTemplate (subject  ?rifrule ) (predicate  <http://white.gobo/modelA#as-defrule> ) (object  ?clipsrule ))
(TripleTemplate (subject  ?rifgroup ) (predicate  <http://www.w3.org/2007/rif#sentences> ) (object  ?sentences ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#numeric-not-equal> ?priority   "0^^http://www.w3.org/2001/XMLSchema#integer"  ))

(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?sentences   ?rifrule  ))

(or
(Member (class  <http://www.w3.org/2007/rif#Implies> ) (instance  ?rifrule ))
(Member (class  <http://www.w3.org/2007/rif#Forall> ) (instance  ?rifrule ))
)
	=>
(assert(TripleTemplate (subject  ?clipsrule ) (predicate  <http://clips.script/salience> ) (object  ?priority ))))

(defrule rule24 (declare (salience 10))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?rifterm ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://example.com/add-as-pattern> ) (object  ?defrule ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

	=>
(assert(Member (instance  ?rifterm ) (class  <http://example.com/ConstraintGenerator> ))))

(deffacts factsd43c760
(Atom (op  <http://example.com/currentdefruleindex> ) (args  "0^^http://www.w3.org/2001/XMLSchema#integer" ))
)

(defrule rule25 (declare (salience 10))
(TripleTemplate (subject  ?rifrule ) (predicate  <http://example.com/add-rule-info> ) (object  ?defrule ))
(TripleTemplate (subject  ?rifaction ) (predicate  <http://example.com/as-action> ) (object  ?action ))
(or
(TripleTemplate (subject  ?rifrule ) (predicate  <http://www.w3.org/2007/rif#then> ) (object  ?rifaction ))
(TripleTemplate (subject  ?rifrule ) (predicate  <http://www.w3.org/2007/rif#formula> ) (object  ?rifaction ))
)
	=>
(assert(TripleTemplate (subject  ?defrule ) (predicate  <http://clips.script/action> ) (object  ?action ))))

(defrule rule26 (declare (salience 10))
(TripleTemplate (subject  ?rifparent ) (predicate  <http://www.w3.org/2007/rif#sentences> ) (object  ?sentencelist ))
(or
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?rifformula ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?sentencelist   ?rifformula  ))

	=>
(assert(Member (instance  ?rifformula ) (class  <http://white.gobo/modelA#RHSPatternGenerator> ))))

(defrule rule27 (declare (salience 10))
(TripleTemplate (subject  ?rifrule ) (predicate  <http://example.com/add-rule-info> ) (object  ?defrule ))
(TripleTemplate (subject  ?rifrule ) (predicate  <http://www.w3.org/2007/rif#formula> ) (object  ?rifclause ))
(or
(Member (class  <http://www.w3.org/2007/rif#Forall> ) (instance  ?rifclause ))
(Member (class  <http://www.w3.org/2007/rif#Implies> ) (instance  ?rifclause ))
)
	=>
(assert(TripleTemplate (subject  ?rifclause ) (predicate  <http://example.com/add-rule-info> ) (object  ?defrule ))))

(defrule rule28 (declare (salience 10))
(TripleTemplate (subject  ?rifdocument ) (predicate  <http://www.w3.org/2007/rif#payload> ) (object  ?rifgroup ))
(not
(exists
(and
(TripleTemplate (subject  ?behavior ) (predicate  <http://www.w3.org/2007/rif#Priority> ) (object  ?x ))
(TripleTemplate (subject  ?rifgroup ) (predicate  <http://www.w3.org/2007/rif#behavior> ) (object  ?behavior ))
)
)
)
	=>
(assert(TripleTemplate (subject  ?rifgroup ) (predicate  <http://white.gobo/local/b/ncfe8f320_n10352#priority> ) (object  "0^^http://www.w3.org/2001/XMLSchema#integer" ))))

(defrule rule29 (declare (salience 10))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://example.com/add-as-pattern> ) (object  ?defrule ))
(or
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?rifterm ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?rifterm ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?rifterm ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?rifterm ))
)
	=>
(assert(Member (instance  ?rifterm ) (class  <http://example.com/ConstraintGenerator> ))))

(defrule rule30 (declare (salience 10))
(Member (class  <http://clips.script/Defrule> ) (instance  ?defrule ))
(Atom (op  <http://example.com/currentdefruleindex> ) (args  ?defruleindex ))
(not
(exists
(TripleTemplate (subject  ?defrule ) (predicate  <http://clips.script/rule-name> ) (object  ?defrulename ))
)
)
(not
(exists
(and
(TripleTemplate (subject  ?x ) (predicate  <http://clips.script/rule-name> ) (object  ?y ))
(test (eq ?y   (<http://www.w3.org/2007/rif-builtin-function#concat> "rule"   ?defruleindex  ) ))

)
)
)
	=>
 (retract(assert(Atom (op  <http://example.com/currentdefruleindex> ) (args  ?defruleindex ))) )(assert(Atom (op  <http://example.com/currentdefruleindex> ) (args  (<http://www.w3.org/2007/rif-builtin-function#numeric-add> ?defruleindex   "1^^http://www.w3.org/2001/XMLSchema#integer"  ))))(assert(TripleTemplate (subject  ?defrule ) (predicate  <http://clips.script/rule-name> ) (object  (<http://www.w3.org/2007/rif-builtin-function#concat> "rule"   ?defruleindex  )))))

(defrule rule31 (declare (salience 10))
(or
(TripleTemplate (subject  ?rifparent ) (predicate  <http://www.w3.org/2007/rif#then> ) (object  ?rifformula ))
(TripleTemplate (subject  ?rifparent ) (predicate  <http://www.w3.org/2007/rif#target> ) (object  ?rifformula ))
)
(or
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?rifformula ))
)
	=>
(assert(Member (instance  ?rifformula ) (class  <http://white.gobo/modelA#RHSPatternGenerator> ))))

(defrule rule32 (declare (salience 10))
(TripleTemplate (subject  ?behavior ) (predicate  <http://www.w3.org/2007/rif#Priority> ) (object  ?priority ))
(TripleTemplate (subject  ?rifgroup ) (predicate  <http://www.w3.org/2007/rif#behavior> ) (object  ?behavior ))
	=>
(assert(TripleTemplate (subject  ?rifgroup ) (predicate  <http://white.gobo/local/b/ncfe8f320_n10352#priority> ) (object  ?priority ))))

(defrule rule33 (declare (salience 10))
(Atom (op  <http://example.com/currentdefruleindex> ) (args  ?defruleindex ))
(TripleTemplate (subject  ?defrule ) (predicate  <http://clips.script/rule-name> ) (object  ?existing ))
(Member (class  <http://clips.script/Defrule> ) (instance  ?defrule ))
(test (eq ?existing   (<http://www.w3.org/2007/rif-builtin-function#concat> "rule"   ?defruleindex  ) ))

	=>
 (retract(assert(Atom (op  <http://example.com/currentdefruleindex> ) (args  ?defruleindex ))) )(assert(Atom (op  <http://example.com/currentdefruleindex> ) (args  (<http://www.w3.org/2007/rif-builtin-function#numeric-add> ?defruleindex   "1^^http://www.w3.org/2001/XMLSchema#integer"  )))))

(defrule rule34
(Member (class  <http://white.gobo/modelA#AtomPatternGenerator> ) (instance  ?rifatom ))
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
(TripleTemplate (subject  ?op ) (predicate  <http://example.com/as-constraint> ) (object  ?constraintop ))
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?op ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?arglist  ))

	=>
 (bind ?pattern   (<http://white.gobo/new-blanknode>) ) (bind ?slotop   (<http://white.gobo/new-blanknode>) ) (bind ?slotargs   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifatom ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?pattern )))(assert(Member (instance  ?pattern ) (class  <http://clips.script/TemplatePatternCE> )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/deftemplate-name> ) (object  "Atom" )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/slot> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?slotop   ?slotargs  ))))(assert(TripleTemplate (subject  ?slotop ) (predicate  <http://clips.script/slot-name> ) (object  "op" )))(assert(TripleTemplate (subject  ?slotop ) (predicate  <http://clips.script/constraint> ) (object  ?constraintop )))(assert(TripleTemplate (subject  ?slotargs ) (predicate  <http://clips.script/slot-name> ) (object  "args" )))(assert(TripleTemplate (subject  ?slotargs ) (predicate  <http://clips.script/constraints> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>))))(assert(TripleTemplate (subject  ?slotargs ) (predicate  <http://white.gobo/local/b/ncfe8f320_n9724#add-atom-args-as-constraint> ) (object  ?arglist ))))

(defrule rule35 (declare (salience -101))
(TripleTemplate (subject  ?rif ) (predicate  <http://white.gobo/local/b/ncfe8f320_n9724#add-atom-args-as-constraint> ) (object  ?arglist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#numeric-greater-than> (<http://www.w3.org/2007/rif-builtin-function#count> ?arglist  )  "0^^http://www.w3.org/2001/XMLSchema#integer"  ))

	=>
(assert(Member (instance  ?rif ) (class  <http://example.com/couldnt-add-all-argument> ))) (<http://white.gobo/set-graph-in-errorstate> "Missing%20argument%20for%20expression%28ex%3Acouldnt-add-all-argument%29"  ))

(defrule rule36 (declare (salience 10))
(TripleTemplate (subject  ?slotargs ) (predicate  <http://white.gobo/local/b/ncfe8f320_n9724#add-atom-args-as-constraint> ) (object  ?arglist ))
(TripleTemplate (subject  ?firstarg ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsexpr ))
(test (eq ?firstarg   (<http://www.w3.org/2007/rif-builtin-function#get> ?arglist   "0^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

	=>
 (bind ?oldconstraints   (do-for-fact (( ?fcct5 TripleTemplate)) (and (eq ?fcct5:subject   ?slotargs  )  (eq ?fcct5:predicate   <http://clips.script/constraints>  ) ) (fact-slot-value ?fcct5   object  ) )  ) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?slotargs  )  (eq ?fct1:predicate   <http://white.gobo/local/b/ncfe8f320_n9724#add-atom-args-as-constraint>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?slotargs ) (predicate  <http://white.gobo/local/b/ncfe8f320_n9724#add-atom-args-as-constraint> ) (object  (<http://www.w3.org/2007/rif-builtin-function#remove> ?arglist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )))) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?slotargs  )  (eq ?fct1:predicate   <http://clips.script/constraints>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?slotargs ) (predicate  <http://clips.script/constraints> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?oldconstraints   ?clipsexpr  )))))

(defrule rule37
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?op ))
(TripleTemplate (subject  ?op ) (predicate  <http://example.com/as-constraint> ) (object  ?constraintop ))
(Member (class  <http://white.gobo/modelA#AtomPatternGenerator> ) (instance  ?rifatom ))
(not
(exists
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
)
)
	=>
 (bind ?slotargs   (<http://white.gobo/new-blanknode>) ) (bind ?slotop   (<http://white.gobo/new-blanknode>) ) (bind ?pattern   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifatom ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?pattern )))(assert(Member (instance  ?pattern ) (class  <http://clips.script/TemplatePatternCE> )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/deftemplate-name> ) (object  "Atom" )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/slot> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?slotop   ?slotargs  ))))(assert(TripleTemplate (subject  ?slotop ) (predicate  <http://clips.script/slot-name> ) (object  "op" )))(assert(TripleTemplate (subject  ?slotop ) (predicate  <http://clips.script/constraint> ) (object  ?constraintop )))(assert(TripleTemplate (subject  ?slotargs ) (predicate  <http://clips.script/slot-name> ) (object  "args" )))(assert(TripleTemplate (subject  ?slotargs ) (predicate  <http://clips.script/constraints> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>)))))

(defrule rule38 (declare (salience -100))
(Member (class  <http://www.w3.org/2007/rif#Do> ) (instance  ?rifnode ))
(exists
(and
(TripleTemplate (subject  ?rifnode ) (predicate  <http://www.w3.org/2007/rif#actionVar> ) (object  ?actionvar ))
(not
(Atom (op  <http://white.gobo/local/b/ncfe8f320_n9420#processed-actionvar> ) (args  ?rifnode  ?actionvar ))
)
)
)
	=>
(assert(Member (instance  ?rifnode ) (class  <http://example.com/missing-actionvar> ))) (<http://white.gobo/set-graph-in-errorstate> "Missing%20binding%20for%20rif%3AactionVar.%28ex%3Amissing-actionvar%29"  ))

(defrule rule39
(TripleTemplate (subject  ?rifdo ) (predicate  <http://example.com/out-transform-do> ) (object  ?actionlist ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-expression> ) (object  ?clipsvar ))
(TripleTemplate (subject  ?rifdo ) (predicate  <http://www.w3.org/2007/rif#actionVar> ) (object  ?actionvar ))
(Member (class  <http://www.w3.org/2007/rif#New> ) (instance  ?rifnew ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?actionvar   ?rifnew  ))

(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifvar ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?actionvar   ?rifvar  ))

(not
(Atom (op  <http://white.gobo/local/b/ncfe8f320_n9420#processed-actionvar> ) (args  ?rifdo  ?actionvar ))
)
	=>
 (bind ?function   (<http://white.gobo/new-blanknode>) ) (bind ?binding   (<http://white.gobo/new-blanknode>) )(assert(Atom (op  <http://white.gobo/local/b/ncfe8f320_n9420#processed-actionvar> ) (args  ?rifdo  ?actionvar ))) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?rifdo  )  (eq ?fct1:predicate   <http://example.com/out-transform-do>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?rifdo ) (predicate  <http://example.com/out-transform-do> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?actionlist   ?function  ))))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-name> ) (object  "bind" )))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?clipsvar   ?binding  ))))(assert(TripleTemplate (subject  ?binding ) (predicate  <http://clips.script/function-name> ) (object  "%3Chttp%3A%2F%2Fwhite.gobo%2Fnew-blanknode%3E" )))(assert(TripleTemplate (subject  ?binding ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>)))))

(defrule rule40 (declare (salience -100))
(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/out-transform-do> ) (object  ?out ))
	=>
(assert(Member (instance  ?rifnode ) (class  <http://example.com/not-completed-actions> ))) (<http://white.gobo/set-graph-in-errorstate> "Actions%20for%20rif%3ADo%20werent%20translated.%28ex%3Anot-completed-actions%29"  ))

(defrule rule41
(TripleTemplate (subject  ?rifnode ) (predicate  <http://www.w3.org/2007/rif#actions> ) (object  ?actionlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?actionlist  ))

	=>
(assert(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/in-transform-do> ) (object  ?actionlist )))(assert(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/out-transform-do> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>)))))

(defrule rule42
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?rifframe ))
(TripleTemplate (subject  ?rifdo ) (predicate  <http://example.com/out-transform-do> ) (object  ?actionlist ))
(TripleTemplate (subject  ?rifdo ) (predicate  <http://www.w3.org/2007/rif#actionVar> ) (object  ?actionvar ))
(TripleTemplate (subject  ?object ) (predicate  <http://example.com/as-expression> ) (object  ?subj ))
(TripleTemplate (subject  ?slotkey ) (predicate  <http://example.com/as-expression> ) (object  ?pred ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?object ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?slotkey ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?slotvalue ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-expression> ) (object  ?clipsvar ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifvar ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?actionvar   ?rifframe  ))

(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?slotlist  ))

(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?actionvar   ?rifvar  ))

(not
(Atom (op  <http://white.gobo/local/b/ncfe8f320_n9420#processed-actionvar> ) (args  ?rifdo  ?actionvar ))
)
	=>
 (bind ?factvar   (<http://white.gobo/new-blanknode>) ) (bind ?function   (<http://white.gobo/new-blanknode>) ) (bind ?extractval   (<http://white.gobo/new-blanknode>) ) (bind ?symbolsubject   (<http://white.gobo/new-blanknode>) ) (bind ?funccheckpred   (<http://white.gobo/new-blanknode>) ) (bind ?binding   (<http://white.gobo/new-blanknode>) ) (bind ?query   (<http://white.gobo/new-blanknode>) ) (bind ?slotsubj   (<http://white.gobo/new-blanknode>) ) (bind ?slotpred   (<http://white.gobo/new-blanknode>) ) (bind ?funcchecksubj   (<http://white.gobo/new-blanknode>) ) (bind ?template   (<http://white.gobo/new-blanknode>) )(assert(Atom (op  <http://white.gobo/local/b/ncfe8f320_n9420#processed-actionvar> ) (args  ?rifdo  ?actionvar ))) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?rifdo  )  (eq ?fct1:predicate   <http://example.com/out-transform-do>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?rifdo ) (predicate  <http://example.com/out-transform-do> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?actionlist   ?function  ))))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-name> ) (object  "bind" )))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?clipsvar   ?binding  ))))(assert(Member (instance  ?binding ) (class  <http://clips.script/DoForFact> )))(assert(TripleTemplate (subject  ?binding ) (predicate  <http://clips.script/fact-set-template> ) (object  ?template )))(assert(TripleTemplate (subject  ?template ) (predicate  <http://clips.script/deftemplate-name> ) (object  "TripleTemplate" )))(assert(TripleTemplate (subject  ?template ) (predicate  <http://clips.script/fact-set-member-variable> ) (object  ?factvar )))(assert(Member (instance  ?factvar ) (class  <http://clips.script/Variable> )))(assert(Member (instance  ?factvar ) (class  <http://example.com/Variable> )))(assert(TripleTemplate (subject  ?binding ) (predicate  <http://clips.script/query> ) (object  ?query )))(assert(TripleTemplate (subject  ?query ) (predicate  <http://clips.script/function-name> ) (object  "and" )))(assert(TripleTemplate (subject  ?query ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?funcchecksubj   ?funccheckpred  ))))(assert(TripleTemplate (subject  ?slotsubj ) (predicate  <http://clips.script/member-variable> ) (object  ?factvar )))(assert(TripleTemplate (subject  ?slotsubj ) (predicate  <http://clips.script/member-slot-name> ) (object  "subject" )))(assert(TripleTemplate (subject  ?funcchecksubj ) (predicate  <http://clips.script/function-name> ) (object  "eq" )))(assert(TripleTemplate (subject  ?funcchecksubj ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?slotsubj   ?subj  ))))(assert(TripleTemplate (subject  ?slotpred ) (predicate  <http://clips.script/member-variable> ) (object  ?factvar )))(assert(TripleTemplate (subject  ?slotpred ) (predicate  <http://clips.script/member-slot-name> ) (object  "predicate" )))(assert(TripleTemplate (subject  ?funccheckpred ) (predicate  <http://clips.script/function-name> ) (object  "eq" )))(assert(TripleTemplate (subject  ?funccheckpred ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?slotpred   ?pred  ))))(assert(TripleTemplate (subject  ?binding ) (predicate  <http://clips.script/action> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?extractval  ))))(assert(TripleTemplate (subject  ?extractval ) (predicate  <http://clips.script/function-name> ) (object  "fact-slot-value" )))(assert(TripleTemplate (subject  ?extractval ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?factvar   ?symbolsubject  ))))(assert(TripleTemplate (subject  ?symbolsubject ) (predicate  <http://clips.script/symbol> ) (object  "object" ))))

(defrule rule43
(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/in-transform-do> ) (object  ?in ))
(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/out-transform-do> ) (object  ?out ))
(test (eq "0^^http://www.w3.org/2001/XMLSchema#integer"   (<http://www.w3.org/2007/rif-builtin-function#count> ?in  ) ))

	=>
(assert(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/as-action> ) (object  ?out ))) (retract(assert(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/in-transform-do> ) (object  ?in ))) ) (retract(assert(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/out-transform-do> ) (object  ?out ))) ))

(defrule rule44
(TripleTemplate (subject  ?firstaction ) (predicate  <http://example.com/as-action> ) (object  ?nextactions ))
(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/out-transform-do> ) (object  ?out ))
(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/in-transform-do> ) (object  ?in ))
(Member (class  <http://www.w3.org/2007/rif#Do> ) (instance  ?rifnode ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#numeric-not-equal> "0^^http://www.w3.org/2001/XMLSchema#integer"   (<http://www.w3.org/2007/rif-builtin-function#count> ?in  ) ))

(test (eq ?firstaction   (<http://www.w3.org/2007/rif-builtin-function#get> ?in   "0^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

(not
(exists
(and
(TripleTemplate (subject  ?rifnode ) (predicate  <http://www.w3.org/2007/rif#actionVar> ) (object  ?actionvar ))
(not
(Atom (op  <http://white.gobo/local/b/ncfe8f320_n9420#processed-actionvar> ) (args  ?rifnode  ?actionvar ))
)
)
)
)
	=>
 (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?rifnode  )  (eq ?fct1:predicate   <http://example.com/in-transform-do>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/in-transform-do> ) (object  (<http://www.w3.org/2007/rif-builtin-function#remove> ?in   "0^^http://www.w3.org/2001/XMLSchema#integer"  )))) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?rifnode  )  (eq ?fct1:predicate   <http://example.com/out-transform-do>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/out-transform-do> ) (object  (<http://www.w3.org/2007/rif-builtin-function#concatenate> ?out   ?nextactions  )))))

(defrule rule45
(TripleTemplate (subject  ?slotvalue ) (predicate  <http://example.com/as-constraint> ) (object  ?constraintobj ))
(TripleTemplate (subject  ?slotkey ) (predicate  <http://example.com/as-constraint> ) (object  ?constraintpred ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?slotkey ))
(TripleTemplate (subject  ?frameobject ) (predicate  <http://example.com/as-constraint> ) (object  ?constraintsubj ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?slotvalue ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?frameobject ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(Member (class  <http://white.gobo/modelA#TripleTemplateGenerator> ) (instance  ?slot ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

(not
(exists
(TripleTemplate (subject  ?slot ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?x ))
)
)
(not
(TripleTemplate (subject  ?slotkey ) (predicate  <http://www.w3.org/2007/rif#constIRI> ) (object  "http%3A%2F%2Fwww.w3.org%2F1999%2F02%2F22-rdf-syntax-ns%23type^^http://www.w3.org/2001/XMLSchema#anyURI" ))
)
	=>
 (bind ?slotpred   (<http://white.gobo/new-blanknode>) ) (bind ?slotobj   (<http://white.gobo/new-blanknode>) ) (bind ?slotsubj   (<http://white.gobo/new-blanknode>) ) (bind ?pattern   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?slot ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?pattern )))(assert(Member (instance  ?pattern ) (class  <http://clips.script/TemplatePatternCE> )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/deftemplate-name> ) (object  "TripleTemplate" )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/slot> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?slotsubj   ?slotpred   ?slotobj  ))))(assert(TripleTemplate (subject  ?slotsubj ) (predicate  <http://clips.script/slot-name> ) (object  "subject" )))(assert(TripleTemplate (subject  ?slotsubj ) (predicate  <http://clips.script/constraint> ) (object  ?constraintsubj )))(assert(TripleTemplate (subject  ?slotpred ) (predicate  <http://clips.script/slot-name> ) (object  "predicate" )))(assert(TripleTemplate (subject  ?slotpred ) (predicate  <http://clips.script/constraint> ) (object  ?constraintpred )))(assert(TripleTemplate (subject  ?slotobj ) (predicate  <http://clips.script/slot-name> ) (object  "object" )))(assert(TripleTemplate (subject  ?slotobj ) (predicate  <http://clips.script/constraint> ) (object  ?constraintobj ))))

(defrule rule46
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?slotvalue ))
(TripleTemplate (subject  ?frameobject ) (predicate  <http://example.com/as-constraint> ) (object  ?constraintsubj ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?slotkey ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(TripleTemplate (subject  ?slotvalue ) (predicate  <http://example.com/as-constraint> ) (object  ?constraintobj ))
(TripleTemplate (subject  ?slotkey ) (predicate  <http://www.w3.org/2007/rif#constIRI> ) (object  "http%3A%2F%2Fwww.w3.org%2F1999%2F02%2F22-rdf-syntax-ns%23type^^http://www.w3.org/2001/XMLSchema#anyURI" ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?frameobject ))
(Member (class  <http://white.gobo/modelA#TripleTemplateGenerator> ) (instance  ?slot ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

(not
(exists
(TripleTemplate (subject  ?slot ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?x ))
)
)
	=>
 (bind ?slotclass   (<http://white.gobo/new-blanknode>) ) (bind ?slotinstance   (<http://white.gobo/new-blanknode>) ) (bind ?pattern   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?slot ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?pattern )))(assert(Member (instance  ?pattern ) (class  <http://clips.script/TemplatePatternCE> )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/deftemplate-name> ) (object  "Member" )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/slot> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?slotinstance   ?slotclass  ))))(assert(TripleTemplate (subject  ?slotinstance ) (predicate  <http://clips.script/slot-name> ) (object  "instance" )))(assert(TripleTemplate (subject  ?slotinstance ) (predicate  <http://clips.script/constraint> ) (object  ?constraintsubj )))(assert(TripleTemplate (subject  ?slotclass ) (predicate  <http://clips.script/slot-name> ) (object  "class" )))(assert(TripleTemplate (subject  ?slotclass ) (predicate  <http://clips.script/constraint> ) (object  ?constraintobj ))))

(defrule rule47
(TripleTemplate (subject  ?rifobject ) (predicate  <http://example.com/as-expression> ) (object  ?subjterm ))
(TripleTemplate (subject  ?clause ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?rifobject ))
(TripleTemplate (subject  ?rifmodify ) (predicate  <http://www.w3.org/2007/rif#target> ) (object  ?clause ))
(Member (class  <http://www.w3.org/2007/rif#Modify> ) (instance  ?rifmodify ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?clause ))
	=>
 (bind ?clipsassert   (<http://white.gobo/new-blanknode>) ) (bind ?slotsubj   (<http://white.gobo/new-blanknode>) ) (bind ?clipsretractvar   (<http://white.gobo/new-blanknode>) ) (bind ?tripletemplate   (<http://white.gobo/new-blanknode>) ) (bind ?comparesubjectandpredicate   (<http://white.gobo/new-blanknode>) ) (bind ?comparepredicate   (<http://white.gobo/new-blanknode>) ) (bind ?tmpvar   (<http://white.gobo/new-blanknode>) ) (bind ?clipsretractall   (<http://white.gobo/new-blanknode>) ) (bind ?comparesubject   (<http://white.gobo/new-blanknode>) )(assert(Member (instance  ?tmpvar ) (class  <http://clips.script/Variable> )))(assert(TripleTemplate (subject  ?clause ) (predicate  <http://example.com/as-expression> ) (object  ?tmpvar )))(assert(TripleTemplate (subject  ?rifmodify ) (predicate  <http://example.com/as-action> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?clipsretractall   ?clipsassert  ))))(assert(Member (instance  ?clipsretractall ) (class  <http://clips.script/DoForAllFacts> )))(assert(TripleTemplate (subject  ?clipsretractall ) (predicate  <http://clips.script/fact-set-template> ) (object  ?tripletemplate )))(assert(TripleTemplate (subject  ?tripletemplate ) (predicate  <http://clips.script/deftemplate-name> ) (object  "TripleTemplate" )))(assert(TripleTemplate (subject  ?tripletemplate ) (predicate  <http://clips.script/fact-set-member-variable> ) (object  ?tmpvar )))(assert(TripleTemplate (subject  ?clipsretractall ) (predicate  <http://clips.script/query> ) (object  ?comparesubjectandpredicate )))(assert(TripleTemplate (subject  ?comparesubjectandpredicate ) (predicate  <http://clips.script/function-name> ) (object  "and" )))(assert(TripleTemplate (subject  ?comparesubjectandpredicate ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?comparesubject   ?comparepredicate  ))))(assert(TripleTemplate (subject  ?comparesubject ) (predicate  <http://clips.script/function-name> ) (object  "eq" )))(assert(TripleTemplate (subject  ?comparesubject ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?slotsubj   ?subjterm  ))))(assert(TripleTemplate (subject  ?slotsubj ) (predicate  <http://clips.script/member-variable> ) (object  ?tmpvar )))(assert(TripleTemplate (subject  ?slotsubj ) (predicate  <http://clips.script/member-slot-name> ) (object  "subject" )))(assert(TripleTemplate (subject  ?comparepredicate ) (predicate  <http://clips.script/function-name> ) (object  "or" )))(assert(TripleTemplate (subject  ?comparepredicate ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>))))(assert(TripleTemplate (subject  ?comparepredicate ) (predicate  <http://example.com/compare-slotkeys-varpredicate-rifframe> ) (object  ?clause )))(assert(TripleTemplate (subject  ?comparepredicate ) (predicate  <http://example.com/compare-slotkeys-varpredicate-tmpvar> ) (object  ?tmpvar )))(assert(TripleTemplate (subject  ?comparepredicate ) (predicate  <http://example.com/add-compare-predicate-from> ) (object  ?clause )))(assert(TripleTemplate (subject  ?clipsretractall ) (predicate  <http://clips.script/action> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?clipsretractvar  ))))(assert(TripleTemplate (subject  ?clipsretractvar ) (predicate  <http://clips.script/function-name> ) (object  "retract" )))(assert(TripleTemplate (subject  ?clipsretractvar ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?tmpvar  ))))(assert(TripleTemplate (subject  ?clipsassert ) (predicate  <http://example.com/assert-uses-pattern-from> ) (object  ?clause ))))

(defrule rule48
(TripleTemplate (subject  ?rifassert ) (predicate  <http://www.w3.org/2007/rif#target> ) (object  ?clause ))
(Member (class  <http://www.w3.org/2007/rif#Assert> ) (instance  ?rifassert ))
(or
(Member (class  <http://www.w3.org/2007/rif#SubClass> ) (instance  ?clause ))
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?clause ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?clause ))
(Member (class  <http://www.w3.org/2007/rif#Member> ) (instance  ?clause ))
)
	=>
 (bind ?clipsaction   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifassert ) (predicate  <http://example.com/as-action> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?clipsaction  ))))(assert(TripleTemplate (subject  ?clipsaction ) (predicate  <http://example.com/assert-uses-pattern-from> ) (object  ?clause ))))

(defrule rule49
(TripleTemplate (subject  ?rifretract ) (predicate  <http://www.w3.org/2007/rif#target> ) (object  ?rifterm ))
(TripleTemplate (subject  ?rifterm ) (predicate  <http://example.com/as-expression> ) (object  ?clipsterm ))
(Member (class  <http://www.w3.org/2007/rif#Retract> ) (instance  ?rifretract ))
	=>
 (bind ?expandtriples   (<http://white.gobo/new-blanknode>) ) (bind ?slotsubj   (<http://white.gobo/new-blanknode>) ) (bind ?findtriples   (<http://white.gobo/new-blanknode>) ) (bind ?triplequery   (<http://white.gobo/new-blanknode>) ) (bind ?tripletemplate   (<http://white.gobo/new-blanknode>) ) (bind ?clipsretract   (<http://white.gobo/new-blanknode>) ) (bind ?tmpvar   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifretract ) (predicate  <http://example.com/as-action> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?clipsretract  ))))(assert(TripleTemplate (subject  ?clipsretract ) (predicate  <http://clips.script/function-name> ) (object  "retract" )))(assert(TripleTemplate (subject  ?clipsretract ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?expandtriples  ))))(assert(TripleTemplate (subject  ?expandtriples ) (predicate  <http://clips.script/function-name> ) (object  "expand%24" )))(assert(TripleTemplate (subject  ?expandtriples ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?findtriples  ))))(assert(Member (instance  ?findtriples ) (class  <http://clips.script/FindAllFacts> )))(assert(TripleTemplate (subject  ?findtriples ) (predicate  <http://clips.script/fact-set-template> ) (object  ?tripletemplate )))(assert(TripleTemplate (subject  ?findtriples ) (predicate  <http://clips.script/query> ) (object  ?triplequery )))(assert(TripleTemplate (subject  ?tripletemplate ) (predicate  <http://clips.script/deftemplate-name> ) (object  "TripleTemplate" )))(assert(TripleTemplate (subject  ?tripletemplate ) (predicate  <http://clips.script/fact-set-member-variable> ) (object  ?tmpvar )))(assert(TripleTemplate (subject  ?triplequery ) (predicate  <http://clips.script/function-name> ) (object  "eq" )))(assert(TripleTemplate (subject  ?triplequery ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?clipsterm   ?slotsubj  ))))(assert(TripleTemplate (subject  ?slotsubj ) (predicate  <http://clips.script/member-variable> ) (object  ?tmpvar )))(assert(TripleTemplate (subject  ?slotsubj ) (predicate  <http://clips.script/member-slot-name> ) (object  "subject" )))(assert(Member (instance  ?tmpvar ) (class  <http://clips.script/Variable> )))(assert(Member (instance  ?tmpvar ) (class  <http://example.com/Variable> ))))

(defrule rule50
(or
(TripleTemplate (subject  ?rifrule ) (predicate  <http://www.w3.org/2007/rif#formula> ) (object  ?clause ))
(TripleTemplate (subject  ?rifrule ) (predicate  <http://www.w3.org/2007/rif#then> ) (object  ?clause ))
)
(or
(Member (class  <http://www.w3.org/2007/rif#SubClass> ) (instance  ?clause ))
(Member (class  <http://www.w3.org/2007/rif#Member> ) (instance  ?clause ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?clause ))
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?clause ))
)
	=>
 (bind ?clipsaction   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?clause ) (predicate  <http://example.com/as-action> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?clipsaction  ))))(assert(TripleTemplate (subject  ?clipsaction ) (predicate  <http://example.com/assert-uses-pattern-from> ) (object  ?clause ))))

(defrule rule51
(TripleTemplate (subject  ?super ) (predicate  <http://example.com/as-expression> ) (object  ?expressionsuper ))
(TripleTemplate (subject  ?sub ) (predicate  <http://example.com/as-expression> ) (object  ?expressionsub ))
(TripleTemplate (subject  ?rifsuperclass ) (predicate  <http://www.w3.org/2007/rif#sub> ) (object  ?sub ))
(TripleTemplate (subject  ?rifsuperclass ) (predicate  <http://www.w3.org/2007/rif#super> ) (object  ?super ))
(Member (class  <http://white.gobo/modelA#RHSPatternGenerator> ) (instance  ?rifsuperclass ))
	=>
 (bind ?slotsub   (<http://white.gobo/new-blanknode>) ) (bind ?slotsuper   (<http://white.gobo/new-blanknode>) ) (bind ?rhspattern   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifsuperclass ) (predicate  <http://example.com/as-rhspattern> ) (object  ?rhspattern )))(assert(TripleTemplate (subject  ?rhspattern ) (predicate  <http://clips.script/deftemplate-name> ) (object  "Subclass" )))(assert(TripleTemplate (subject  ?rhspattern ) (predicate  <http://clips.script/slot> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?slotsub   ?slotsuper  ))))(assert(TripleTemplate (subject  ?slotsub ) (predicate  <http://clips.script/slot-name> ) (object  "sub" )))(assert(TripleTemplate (subject  ?slotsub ) (predicate  <http://clips.script/field> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?expressionsub  ))))(assert(TripleTemplate (subject  ?slotsuper ) (predicate  <http://clips.script/slot-name> ) (object  "super" )))(assert(TripleTemplate (subject  ?slotsuper ) (predicate  <http://clips.script/field> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?expressionsuper  )))))

(defrule rule52 (declare (salience 10))
(TripleTemplate (subject  ?slotargs ) (predicate  <http://example.com/add-atom-args-rhspattern> ) (object  ?list ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#numeric-equal> "0^^http://www.w3.org/2001/XMLSchema#integer"   (<http://www.w3.org/2007/rif-builtin-function#count> ?list  ) ))

	=>
 (retract(assert(TripleTemplate (subject  ?slotargs ) (predicate  <http://example.com/add-atom-args-rhspattern> ) (object  ?list ))) ))

(defrule rule53
(TripleTemplate (subject  ?op ) (predicate  <http://example.com/as-expression> ) (object  ?expressionop ))
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?op ))
(Member (class  <http://white.gobo/modelA#RHSPatternGenerator> ) (instance  ?rifatom ))
(not
(exists
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
)
)
	=>
 (bind ?slotop   (<http://white.gobo/new-blanknode>) ) (bind ?rhspattern   (<http://white.gobo/new-blanknode>) ) (bind ?slotargs   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifatom ) (predicate  <http://example.com/as-rhspattern> ) (object  ?rhspattern )))(assert(TripleTemplate (subject  ?rhspattern ) (predicate  <http://clips.script/deftemplate-name> ) (object  "Atom" )))(assert(TripleTemplate (subject  ?rhspattern ) (predicate  <http://clips.script/slot> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?slotop   ?slotargs  ))))(assert(TripleTemplate (subject  ?slotop ) (predicate  <http://clips.script/slot-name> ) (object  "op" )))(assert(TripleTemplate (subject  ?slotop ) (predicate  <http://clips.script/field> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?expressionop  ))))(assert(TripleTemplate (subject  ?slotargs ) (predicate  <http://clips.script/slot-name> ) (object  "args" )))(assert(TripleTemplate (subject  ?slotargs ) (predicate  <http://clips.script/field> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>)))))

(defrule rule54
(Member (class  <http://www.w3.org/2007/rif#Retract> ) (instance  ?rifretract ))
(TripleTemplate (subject  ?rifretract ) (predicate  <http://www.w3.org/2007/rif#target> ) (object  ?clause ))
(or
(Member (class  <http://www.w3.org/2007/rif#Member> ) (instance  ?clause ))
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?clause ))
(Member (class  <http://www.w3.org/2007/rif#SubClass> ) (instance  ?clause ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?clause ))
)
	=>
 (bind ?clipsaction   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifretract ) (predicate  <http://example.com/as-action> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?clipsaction  ))))(assert(TripleTemplate (subject  ?clipsaction ) (predicate  <http://clips.script/function-name> ) (object  "retract" )))(assert(TripleTemplate (subject  ?clipsaction ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>))))(assert(TripleTemplate (subject  ?clipsaction ) (predicate  <http://example.com/retract-uses-pattern-from> ) (object  ?clause ))))

(defrule rule55
(TripleTemplate (subject  ?rifmember ) (predicate  <http://www.w3.org/2007/rif#instance> ) (object  ?instance ))
(TripleTemplate (subject  ?cls ) (predicate  <http://example.com/as-expression> ) (object  ?expressioncls ))
(TripleTemplate (subject  ?rifmember ) (predicate  <http://www.w3.org/2007/rif#class> ) (object  ?cls ))
(TripleTemplate (subject  ?instance ) (predicate  <http://example.com/as-expression> ) (object  ?expressioninstance ))
(Member (class  <http://white.gobo/modelA#RHSPatternGenerator> ) (instance  ?rifmember ))
	=>
 (bind ?rhspattern   (<http://white.gobo/new-blanknode>) ) (bind ?slotinstance   (<http://white.gobo/new-blanknode>) ) (bind ?slotcls   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifmember ) (predicate  <http://example.com/as-rhspattern> ) (object  ?rhspattern )))(assert(TripleTemplate (subject  ?rhspattern ) (predicate  <http://clips.script/deftemplate-name> ) (object  "Member" )))(assert(TripleTemplate (subject  ?rhspattern ) (predicate  <http://clips.script/slot> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?slotinstance   ?slotcls  ))))(assert(TripleTemplate (subject  ?slotinstance ) (predicate  <http://clips.script/slot-name> ) (object  "instance" )))(assert(TripleTemplate (subject  ?slotinstance ) (predicate  <http://clips.script/field> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?expressioninstance  ))))(assert(TripleTemplate (subject  ?slotcls ) (predicate  <http://clips.script/slot-name> ) (object  "class" )))(assert(TripleTemplate (subject  ?slotcls ) (predicate  <http://clips.script/field> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?expressioncls  )))))

(defrule rule56
(TripleTemplate (subject  ?rifformula ) (predicate  <http://example.com/as-rhspattern> ) (object  ?rhspattern ))
(TripleTemplate (subject  ?clipsretract ) (predicate  <http://example.com/retract-uses-pattern-from> ) (object  ?rifformula ))
	=>
 (bind ?clipsassert   (<http://white.gobo/new-blanknode>) ) (bind ?retracttargets   (do-for-fact (( ?fcct6 TripleTemplate)) (and (eq ?fcct6:subject   ?clipsretract  )  (eq ?fcct6:predicate   <http://clips.script/function-args>  ) ) (fact-slot-value ?fcct6   object  ) )  ) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?clipsretract  )  (eq ?fct1:predicate   <http://clips.script/function-args>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?clipsretract ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?retracttargets   ?clipsassert  ))))(assert(TripleTemplate (subject  ?clipsassert ) (predicate  <http://clips.script/assert> ) (object  ?rhspattern ))))

(defrule rule57
(TripleTemplate (subject  ?clipsassert ) (predicate  <http://example.com/assert-uses-pattern-from> ) (object  ?rifformula ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://example.com/as-rhspattern> ) (object  ?rhspattern ))
	=>
(assert(TripleTemplate (subject  ?clipsassert ) (predicate  <http://clips.script/assert> ) (object  ?rhspattern ))))

(defrule rule58 (declare (salience -100))
(TripleTemplate (subject  ?clipsfunction ) (predicate  <http://example.com/add-atom-args-rhspattern> ) (object  ?rifrestargs ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#numeric-not-equal> "0^^http://www.w3.org/2001/XMLSchema#integer"   (<http://www.w3.org/2007/rif-builtin-function#count> ?rifrestargs  ) ))

	=>
(assert(Member (instance  ?clipsfunction ) (class  <http://example.com/cant-translate-atom-as-rhspattern> ))) (<http://white.gobo/set-graph-in-errorstate> "Translation%20of%20rif%3AAtom%20to%20rhs-pattern%20failed.%20Didnt%20translated%20all%20rif%3Aargs.%28ex%3Acant-translate-atom-as-rhspattern%29"  ))

(defrule rule59
(TripleTemplate (subject  ?slotkey ) (predicate  <http://example.com/as-expression> ) (object  ?slotkeyterm ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?slotkey ))
(TripleTemplate (subject  ?comparepredicate ) (predicate  <http://example.com/compare-slotkeys-varpredicate-tmpvar> ) (object  ?tmpvar ))
(TripleTemplate (subject  ?comparepredicate ) (predicate  <http://example.com/compare-slotkeys-varpredicate-rifframe> ) (object  ?rifframe ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?slotlist  ))

(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

(test (eq "1^^http://www.w3.org/2001/XMLSchema#integer"   (<http://www.w3.org/2007/rif-builtin-function#count> ?slotlist  ) ))

	=>
 (bind ?slotpred   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?slotpred ) (predicate  <http://clips.script/member-variable> ) (object  ?tmpvar )))(assert(TripleTemplate (subject  ?slotpred ) (predicate  <http://clips.script/member-slot-name> ) (object  "predicate" ))) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?comparepredicate  )  (eq ?fct1:predicate   <http://clips.script/function-name>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?comparepredicate ) (predicate  <http://clips.script/function-name> ) (object  "eq" ))) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?comparepredicate  )  (eq ?fct1:predicate   <http://clips.script/function-args>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?comparepredicate ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?slotpred   ?slotkeyterm  )))))

(defrule rule60
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?slotkey ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?slotvalue ))
(TripleTemplate (subject  ?rifnode ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(TripleTemplate (subject  ?rifnode ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?object ))
(TripleTemplate (subject  ?slotkey ) (predicate  <http://example.com/as-expression> ) (object  ?expressionpredicate ))
(TripleTemplate (subject  ?object ) (predicate  <http://example.com/as-expression> ) (object  ?expressionsubject ))
(TripleTemplate (subject  ?slotvalue ) (predicate  <http://example.com/as-expression> ) (object  ?expressionobject ))
(Member (class  <http://white.gobo/modelA#RHSPatternGenerator> ) (instance  ?rifnode ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?slotlist  ))

	=>
 (bind ?slotsubject   (<http://white.gobo/new-blanknode>) ) (bind ?slotpredicate   (<http://white.gobo/new-blanknode>) ) (bind ?rhspattern   (<http://white.gobo/new-blanknode>) ) (bind ?slotobject   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/as-rhspattern> ) (object  ?rhspattern )))(assert(TripleTemplate (subject  ?rhspattern ) (predicate  <http://clips.script/deftemplate-name> ) (object  "TripleTemplate" )))(assert(TripleTemplate (subject  ?rhspattern ) (predicate  <http://clips.script/slot> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?slotsubject   ?slotpredicate   ?slotobject  ))))(assert(TripleTemplate (subject  ?slotsubject ) (predicate  <http://clips.script/slot-name> ) (object  "subject" )))(assert(TripleTemplate (subject  ?slotsubject ) (predicate  <http://clips.script/field> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?expressionsubject  ))))(assert(TripleTemplate (subject  ?slotpredicate ) (predicate  <http://clips.script/slot-name> ) (object  "predicate" )))(assert(TripleTemplate (subject  ?slotpredicate ) (predicate  <http://clips.script/field> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?expressionpredicate  ))))(assert(TripleTemplate (subject  ?slotobject ) (predicate  <http://clips.script/slot-name> ) (object  "object" )))(assert(TripleTemplate (subject  ?slotobject ) (predicate  <http://clips.script/field> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?expressionobject  )))))

(defrule rule61
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?op ))
(TripleTemplate (subject  ?op ) (predicate  <http://example.com/as-expression> ) (object  ?expressionop ))
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
(Member (class  <http://white.gobo/modelA#RHSPatternGenerator> ) (instance  ?rifatom ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?arglist  ))

	=>
 (bind ?rhspattern   (<http://white.gobo/new-blanknode>) ) (bind ?slotargs   (<http://white.gobo/new-blanknode>) ) (bind ?slotop   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifatom ) (predicate  <http://example.com/as-rhspattern> ) (object  ?rhspattern )))(assert(TripleTemplate (subject  ?rhspattern ) (predicate  <http://clips.script/deftemplate-name> ) (object  "Atom" )))(assert(TripleTemplate (subject  ?rhspattern ) (predicate  <http://clips.script/slot> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?slotop   ?slotargs  ))))(assert(TripleTemplate (subject  ?slotop ) (predicate  <http://clips.script/slot-name> ) (object  "op" )))(assert(TripleTemplate (subject  ?slotop ) (predicate  <http://clips.script/field> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?expressionop  ))))(assert(TripleTemplate (subject  ?slotargs ) (predicate  <http://clips.script/slot-name> ) (object  "args" )))(assert(TripleTemplate (subject  ?slotargs ) (predicate  <http://clips.script/field> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>))))(assert(TripleTemplate (subject  ?slotargs ) (predicate  <http://example.com/add-atom-args-rhspattern> ) (object  ?arglist ))))

(defrule rule62 (declare (salience 10))
(TripleTemplate (subject  ?firstarg ) (predicate  <http://example.com/as-expression> ) (object  ?clipsexpr ))
(TripleTemplate (subject  ?slotargs ) (predicate  <http://example.com/add-atom-args-rhspattern> ) (object  ?arglist ))
(test (eq ?firstarg   (<http://www.w3.org/2007/rif-builtin-function#get> ?arglist   "0^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

	=>
 (bind ?oldfield   (do-for-fact (( ?fcct7 TripleTemplate)) (and (eq ?fcct7:subject   ?slotargs  )  (eq ?fcct7:predicate   <http://clips.script/field>  ) ) (fact-slot-value ?fcct7   object  ) )  ) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?slotargs  )  (eq ?fct1:predicate   <http://example.com/add-atom-args-rhspattern>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?slotargs ) (predicate  <http://example.com/add-atom-args-rhspattern> ) (object  (<http://www.w3.org/2007/rif-builtin-function#remove> ?arglist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )))) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?slotargs  )  (eq ?fct1:predicate   <http://clips.script/field>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?slotargs ) (predicate  <http://clips.script/field> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?oldfield   ?clipsexpr  )))))

(defrule rule63 (declare (salience 100))
(TripleTemplate (subject  ?child ) (predicate  <http://white.gobo/local/b/ncfe8f320_n7026#give-inheritance> ) (object  ?target ))
(or
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#target> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#instance> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#class> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#sub> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#rest> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#meta> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#content> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#then> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#pattern> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#super> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#if> ) (object  ?child ))
)
	=>
(assert(TripleTemplate (subject  ?parent ) (predicate  <http://white.gobo/local/b/ncfe8f320_n7026#give-inheritance> ) (object  ?target ))))

(defrule rule64 (declare (salience 100))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(TripleTemplate (subject  ?child ) (predicate  <http://white.gobo/local/b/ncfe8f320_n7026#give-inheritance> ) (object  ?target ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?slotlist  ))

(or
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?child ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?child ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

	=>
(assert(TripleTemplate (subject  ?parent ) (predicate  <http://white.gobo/local/b/ncfe8f320_n7026#give-inheritance> ) (object  ?target ))))

(defrule rule65 (declare (salience 100))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?childvalue ))
(Atom (op  <http://white.gobo/local/b/ncfe8f320_n7026#always-wrong> ) (args ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?slotlist  ))

(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

(not
(exists
(or
(TripleTemplate (subject  ?childvalue ) (predicate  <http://www.w3.org/2007/rif#constIRI> ) (object  ?x ))
(TripleTemplate (subject  ?childvalue ) (predicate  <http://www.w3.org/2007/rif#value> ) (object  ?x ))
)
)
)
	=>
(assert(TripleTemplate (subject  ?parent ) (predicate  <http://example.com/inherits-data> ) (object  ?childvalue ))))

(defrule rule66 (declare (salience 100))
(TripleTemplate (subject  ?rifdo ) (predicate  <http://www.w3.org/2007/rif#actionVar> ) (object  ?actionvar ))
(TripleTemplate (subject  ?child ) (predicate  <http://white.gobo/local/b/ncfe8f320_n7026#give-inheritance> ) (object  ?target ))
(test (eq ?child   (<http://www.w3.org/2007/rif-builtin-function#get> ?actionvar   "1^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

	=>
(assert(TripleTemplate (subject  ?target ) (predicate  <http://white.gobo/local/b/ncfe8f320_n7026#rifdoinheritance> ) (object  ?rifdo ))))

(defrule rule67 (declare (salience 100))
(Atom (op  <http://white.gobo/local/b/ncfe8f320_n7026#always-wrong> ) (args ))
(TripleTemplate (subject  ?atom ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?childlist ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#content> ) (object  ?atom ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?childlist  ))

(or
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Const> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?child ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?childlist   ?child  ))

(not
(exists
(or
(TripleTemplate (subject  ?child ) (predicate  <http://www.w3.org/2007/rif#value> ) (object  ?x ))
(TripleTemplate (subject  ?child ) (predicate  <http://www.w3.org/2007/rif#constIRI> ) (object  ?x ))
)
)
)
	=>
(assert(TripleTemplate (subject  ?parent ) (predicate  <http://example.com/inherits-data> ) (object  ?child ))))

(defrule rule68 (declare (salience 100))
(TripleTemplate (subject  ?rifforall ) (predicate  <http://www.w3.org/2007/rif#vars> ) (object  ?varlist ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifvar ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?varlist   ?rifvar  ))

(Atom (op  <http://white.gobo/local/b/ncfe8f320_n7026#always-wrong> ) (args ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?varlist  ))

	=>
(assert(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/inherits-data> ) (object  ?rifforall ))))

(defrule rule69 (declare (salience 100))
(TripleTemplate (subject  ?parent ) (predicate  <http://example.com/inherits-data> ) (object  ?child ))
(TripleTemplate (subject  ?child ) (predicate  <http://example.com/inherits-data> ) (object  ?grandchild ))
(Atom (op  <http://white.gobo/local/b/ncfe8f320_n7026#always-wrong> ) (args ))
(or
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?grandchild ))
(Member (class  <http://www.w3.org/2007/rif#Const> ) (instance  ?grandchild ))
(Member (class  <http://www.w3.org/2007/rif#INeg> ) (instance  ?grandchild ))
)
	=>
(assert(TripleTemplate (subject  ?parent ) (predicate  <http://example.com/inherits-data> ) (object  ?grandchild ))))

(defrule rule70 (declare (salience 100))
(Atom (op  <http://white.gobo/local/b/ncfe8f320_n7026#always-wrong> ) (args ))
(or
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#formulas> ) (object  ?childlist ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#sentences> ) (object  ?childlist ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#items> ) (object  ?childlist ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?childlist ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#actions> ) (object  ?childlist ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?childlist  ))

(or
(Member (class  <http://www.w3.org/2007/rif#Exists> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Const> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Assert> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#INeg> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Or> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Retract> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Forall> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Execute> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Equal> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Not> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Group> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Do> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Subclass> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Modify> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Member> ) (instance  ?child ))
)
(not
(exists
(or
(TripleTemplate (subject  ?child ) (predicate  <http://www.w3.org/2007/rif#constIRI> ) (object  ?x ))
(TripleTemplate (subject  ?child ) (predicate  <http://www.w3.org/2007/rif#value> ) (object  ?x ))
)
)
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?childlist   ?child  ))

	=>
(assert(TripleTemplate (subject  ?parent ) (predicate  <http://example.com/inherits-data> ) (object  ?child ))))

(defrule rule71 (declare (salience 100))
(TripleTemplate (subject  ?rifdo ) (predicate  <http://www.w3.org/2007/rif#actions> ) (object  ?childlist ))
(TripleTemplate (subject  ?child ) (predicate  <http://white.gobo/local/b/ncfe8f320_n7026#give-inheritance> ) (object  ?target ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?childlist   ?child  ))

	=>
(assert(TripleTemplate (subject  ?target ) (predicate  <http://white.gobo/local/b/ncfe8f320_n7026#rifdoinheritance> ) (object  ?rifdo ))))

(defrule rule72 (declare (salience 100))
(TripleTemplate (subject  ?document ) (predicate  <http://white.gobo/local/b/ncfe8f320_n7026#give-inheritance> ) (object  ?localconst ))
(Member (class  <http://www.w3.org/2007/rif#Document> ) (instance  ?document ))
	=>
(assert(TripleTemplate (subject  ?document ) (predicate  <http://example.com/inherits-data> ) (object  ?localconst ))))

(defrule rule73 (declare (salience 100))
(TripleTemplate (subject  ?child ) (predicate  <http://white.gobo/local/b/ncfe8f320_n7026#give-inheritance> ) (object  ?target ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#formula> ) (object  ?child ))
(not
(exists
(and
(TripleTemplate (subject  ?var ) (predicate  <http://www.w3.org/2007/rif#varname> ) (object  ?name ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#vars> ) (object  ?varlist ))
(TripleTemplate (subject  ?target ) (predicate  <http://www.w3.org/2007/rif#varname> ) (object  ?name ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?varlist   ?var  ))

)
)
)
	=>
(assert(TripleTemplate (subject  ?parent ) (predicate  <http://white.gobo/local/b/ncfe8f320_n7026#give-inheritance> ) (object  ?target ))))

(defrule rule74 (declare (salience 100))
(Atom (op  <http://white.gobo/local/b/ncfe8f320_n7026#always-wrong> ) (args ))
(TripleTemplate (subject  ?rifdo ) (predicate  <http://www.w3.org/2007/rif#actionVar> ) (object  ?actionvar ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?binding ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?actionvar   ?binding  ))

(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?actionvar  ))

	=>
(assert(TripleTemplate (subject  ?rifdo ) (predicate  <http://example.com/inherits-data> ) (object  ?binding ))))

(defrule rule75 (declare (salience 100))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?rifconstraint ))
(TripleTemplate (subject  ?rifconstraint ) (predicate  <http://white.gobo/local/b/ncfe8f320_n7026#give-inheritance> ) (object  ?target ))
(or
(Member (class  <http://white.gobo/modelA#ConditionGenerator> ) (instance  ?rifconstraint ))
(Member (class  <http://white.gobo/modelA#ConstraintGenerator> ) (instance  ?rifconstraint ))
)
	=>
(assert(TripleTemplate (subject  ?rifconstraint ) (predicate  <http://example.com/inherits-data> ) (object  ?target ))))

(defrule rule76 (declare (salience 100))
(Atom (op  <http://white.gobo/local/b/ncfe8f320_n7026#always-wrong> ) (args ))
(or
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#meta> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#pattern> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#class> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#super> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#payload> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#rest> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#if> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#instance> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#formula> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#then> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#target> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#sub> ) (object  ?child ))
)
(not
(exists
(or
(TripleTemplate (subject  ?child ) (predicate  <http://www.w3.org/2007/rif#value> ) (object  ?x ))
(TripleTemplate (subject  ?child ) (predicate  <http://www.w3.org/2007/rif#constIRI> ) (object  ?x ))
)
)
)
	=>
(assert(TripleTemplate (subject  ?parent ) (predicate  <http://example.com/inherits-data> ) (object  ?child ))))

(defrule rule77 (declare (salience 100))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#vars> ) (object  ?varlist ))
(TripleTemplate (subject  ?target ) (predicate  <http://www.w3.org/2007/rif#varname> ) (object  ?name ))
(TripleTemplate (subject  ?child ) (predicate  <http://white.gobo/local/b/ncfe8f320_n7026#give-inheritance> ) (object  ?target ))
(TripleTemplate (subject  ?var ) (predicate  <http://www.w3.org/2007/rif#varname> ) (object  ?name ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#formula> ) (object  ?child ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?varlist   ?var  ))

	=>
(assert(TripleTemplate (subject  ?var ) (predicate  <http://example.com/inherits-data> ) (object  ?target ))))

(defrule rule78 (declare (salience 100))
(TripleTemplate (subject  ?rifdo ) (predicate  <http://www.w3.org/2007/rif#actionVar> ) (object  ?actionvar ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?var ))
(test (eq ?var   (<http://www.w3.org/2007/rif-builtin-function#get> ?actionvar   "0^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

(Member (class  <http://www.w3.org/2007/rif#New> ) (instance  ?assign ))
(test (eq ?assign   (<http://www.w3.org/2007/rif-builtin-function#get> ?actionvar   "1^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

	=>
(assert(Member (instance  ?var ) (class  <http://white.gobo/modelA#NewVar> ))))

(defrule rule79 (declare (salience 100))
(or
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#items> ) (object  ?arglist ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?arglist  ))

(or
(and
(Member (class  <http://www.w3.org/2007/rif#Const> ) (instance  ?child ))
(exists
(TripleTemplate (subject  ?child ) (predicate  <http://www.w3.org/2007/rif#constname> ) (object  ?x ))
)
)
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?child ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?arglist   ?child  ))

	=>
(assert(TripleTemplate (subject  ?parent ) (predicate  <http://white.gobo/local/b/ncfe8f320_n7026#give-inheritance> ) (object  ?child ))))

(defrule rule80 (declare (salience 100))
(TripleTemplate (subject  ?target ) (predicate  <http://white.gobo/local/b/ncfe8f320_n7026#rifdoinheritance> ) (object  ?parent ))
(not
(exists
(and
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#actionVar> ) (object  ?actionvar ))
(TripleTemplate (subject  ?var ) (predicate  <http://www.w3.org/2007/rif#varname> ) (object  ?name ))
(TripleTemplate (subject  ?target ) (predicate  <http://www.w3.org/2007/rif#varname> ) (object  ?name ))
(test (eq ?var   (<http://www.w3.org/2007/rif-builtin-function#get> ?actionvar   "0^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

)
)
)
	=>
(assert(TripleTemplate (subject  ?parent ) (predicate  <http://white.gobo/local/b/ncfe8f320_n7026#give-inheritance> ) (object  ?target ))))

(defrule rule81 (declare (salience 100))
(or
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#instance> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#sub> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#super> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#target> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#rest> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#class> ) (object  ?child ))
)
(or
(exists
(TripleTemplate (subject  ?child ) (predicate  <http://www.w3.org/2007/rif#constname> ) (object  ?x ))
)
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?child ))
)
	=>
(assert(TripleTemplate (subject  ?parent ) (predicate  <http://white.gobo/local/b/ncfe8f320_n7026#give-inheritance> ) (object  ?child ))))

(defrule rule82 (declare (salience 100))
(TripleTemplate (subject  ?child ) (predicate  <http://white.gobo/local/b/ncfe8f320_n7026#give-inheritance> ) (object  ?target ))
(or
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#sentences> ) (object  ?childlist ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?childlist ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#formulas> ) (object  ?childlist ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?childlist   ?child  ))

(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?childlist  ))

	=>
(assert(TripleTemplate (subject  ?parent ) (predicate  <http://white.gobo/local/b/ncfe8f320_n7026#give-inheritance> ) (object  ?target ))))

(defrule rule83 (declare (salience 100))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?target ))
(TripleTemplate (subject  ?rifnot ) (predicate  <http://white.gobo/local/b/ncfe8f320_n7026#give-inheritance> ) (object  ?target ))
(or
(Member (class  <http://www.w3.org/2007/rif#Or> ) (instance  ?rifnot ))
(Member (class  <http://www.w3.org/2007/rif#Exists> ) (instance  ?rifnot ))
(Member (class  <http://www.w3.org/2007/rif#INeg> ) (instance  ?rifnot ))
)
	=>
(assert(TripleTemplate (subject  ?rifnot ) (predicate  <http://example.com/inherits-data> ) (object  ?target ))))

(defrule rule84 (declare (salience 100))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?target ))
(TripleTemplate (subject  ?term ) (predicate  <http://white.gobo/local/b/ncfe8f320_n7026#give-inheritance> ) (object  ?target ))
(Member (class  <http://white.gobo/modelA#ConditionGenerator> ) (instance  ?rifformula ))
(or
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?term ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?term ))
)
	=>
(assert(TripleTemplate (subject  ?term ) (predicate  <http://example.com/inherits-data> ) (object  ?target ))))

(defrule rule85 (declare (salience 100))
(Atom (op  <http://white.gobo/local/b/ncfe8f320_n7026#always-wrong> ) (args ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?childkey ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?slotlist  ))

(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

(not
(exists
(or
(TripleTemplate (subject  ?childkey ) (predicate  <http://www.w3.org/2007/rif#constIRI> ) (object  ?x ))
(TripleTemplate (subject  ?childkey ) (predicate  <http://www.w3.org/2007/rif#value> ) (object  ?x ))
)
)
)
	=>
(assert(TripleTemplate (subject  ?parent ) (predicate  <http://example.com/inherits-data> ) (object  ?childkey ))))

(defrule rule86 (declare (salience 100))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?slotlist  ))

(or
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?child ))
(exists
(TripleTemplate (subject  ?child ) (predicate  <http://www.w3.org/2007/rif#constname> ) (object  ?x ))
)
)
(or
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?child ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?child ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

	=>
(assert(TripleTemplate (subject  ?parent ) (predicate  <http://white.gobo/local/b/ncfe8f320_n7026#give-inheritance> ) (object  ?child ))))

(defrule rule87 (declare (salience 100))
(TripleTemplate (subject  ?document ) (predicate  <http://www.w3.org/2007/rif#payload> ) (object  ?group ))
(TripleTemplate (subject  ?group ) (predicate  <http://white.gobo/local/b/ncfe8f320_n7026#give-inheritance> ) (object  ?localconst ))
	=>
(assert(TripleTemplate (subject  ?document ) (predicate  <http://example.com/inherits-data> ) (object  ?localconst ))))

(defrule rule88 (declare (salience 100))
(TripleTemplate (subject  ?var ) (predicate  <http://www.w3.org/2007/rif#varname> ) (object  ?name ))
(TripleTemplate (subject  ?target ) (predicate  <http://www.w3.org/2007/rif#varname> ) (object  ?name ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#actionVar> ) (object  ?actionvar ))
(TripleTemplate (subject  ?target ) (predicate  <http://white.gobo/local/b/ncfe8f320_n7026#rifdoinheritance> ) (object  ?parent ))
(test (eq ?var   (<http://www.w3.org/2007/rif-builtin-function#get> ?actionvar   "0^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

	=>
(assert(TripleTemplate (subject  ?var ) (predicate  <http://example.com/inherits-data> ) (object  ?target ))))

(defrule rule89 (declare (salience 5))
(TripleTemplate (subject  ?riflist ) (predicate  <http://www.w3.org/2007/rif#items> ) (object  ?itemlist ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#expression-needs-var> ) (object  ?clipsexpression ))
(Member (class  <http://white.gobo/modelA#ExpressionGenerator> ) (instance  ?riflist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?itemlist   ?rifvar  ))

	=>
(assert(TripleTemplate (subject  ?rifvar ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#expression-needs-var> ) (object  ?clipsexpression ))))

(defrule rule90 (declare (salience 5))
(TripleTemplate (subject  ?rifrule ) (predicate  <http://www.w3.org/2007/rif#formula> ) (object  ?rifformula ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?clipsconstraint ))
(or
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#Member> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#Equal> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?rifformula ))
)
	=>
(assert(TripleTemplate (subject  ?rifformula ) (predicate  <http://white.gobo/modelA#bound-variable> ) (object  ?clipsconstraint ))))

(defrule rule91 (declare (salience -1))
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?subpattern ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#formulalist> ) (object  ?formulalist ))
(TripleTemplate (subject  ?superpattern ) (predicate  <http://clips.script/conditional-element> ) (object  ?patternlist ))
(test (eq ?formula   (<http://www.w3.org/2007/rif-builtin-function#get> ?formulalist   "0^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

(not
(exists
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#lhs-pattern-after-conditions> ) (object  ?aftercondition ))
)
)
(not
(Member (class  <http://white.gobo/modelA#MultiPatternGenerator> ) (instance  ?formula ))
)
(or
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?superpattern ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/modelA#as-defrule> ) (object  ?superpattern ))
)
(or
(Member (class  <http://clips.script/OrCE> ) (instance  ?superpattern ))
(Member (class  <http://clips.script/NotCE> ) (instance  ?superpattern ))
(Member (class  <http://clips.script/AndCE> ) (instance  ?superpattern ))
(Member (class  <http://clips.script/ExistsCE> ) (instance  ?superpattern ))
(Member (class  <http://clips.script/Defrule> ) (instance  ?superpattern ))
)
	=>
 (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?formulacontainer  )  (eq ?fct1:predicate   <http://white.gobo/local/b/ncfe8f320_n6144#formulalist>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#remove> ?formulalist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )))) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?superpattern  )  (eq ?fct1:predicate   <http://clips.script/conditional-element>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?superpattern ) (predicate  <http://clips.script/conditional-element> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?patternlist   ?subpattern  ))))(assert(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#transfer-variable-binding> ) (object  ?formulacontainer ))))

(defrule rule92 (declare (salience 5))
(Member (class  <http://www.w3.org/2007/rif#INeg> ) (instance  ?formula ))
	=>
 (bind ?clipsnot   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>))))(assert(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?clipsnot )))(assert(Member (instance  ?clipsnot ) (class  <http://clips.script/NotCE> )))(assert(TripleTemplate (subject  ?clipsnot ) (predicate  <http://clips.script/conditional-element> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>)))))

(defrule rule93 (declare (salience 5))
(or
(Member (class  <http://www.w3.org/2007/rif#INeg> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#SubClass> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#Equal> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#Member> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#Or> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#Exists> ) (instance  ?formula ))
)
	=>
(assert(Member (instance  ?formula ) (class  <http://white.gobo/local/b/ncfe8f320_n6144#rifformula> ))))

(defrule rule94 (declare (salience -10))
(TripleTemplate (subject  ?superpattern ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#formulalist> ) (object  ?formulalist ))
(TripleTemplate (subject  ?superpattern ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#add-pattern-from> ) (object  ?subpattern ))
(not
(TripleTemplate (subject  ?superpattern ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?subpattern ))
)
(or
(Member (class  <http://www.w3.org/2007/rif#Or> ) (instance  ?subpattern ))
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?subpattern ))
(Member (class  <http://www.w3.org/2007/rif#Implies> ) (instance  ?subpattern ))
)
(not
(exists
(and
(TripleTemplate (subject  ?subpattern ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#constraints-needs-variable> ) (object  ?x ))
(not
(TripleTemplate (subject  ?subpattern ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?x ))
)
)
)
)
(not
(exists
(and
(TripleTemplate (subject  ?subpattern ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#add-pattern-from> ) (object  ?subsub ))
(not
(TripleTemplate (subject  ?subpattern ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?subsub ))
)
)
)
)
	=>
(assert(TripleTemplate (subject  ?superpattern ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?subpattern ))) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?superpattern  )  (eq ?fct1:predicate   <http://white.gobo/local/b/ncfe8f320_n6144#formulalist>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?superpattern ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?formulalist   ?subpattern  )))))

(defrule rule95 (declare (salience 5))
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?rifand ))
(not
(exists
(TripleTemplate (subject  ?superrule ) (predicate  <http://www.w3.org/2007/rif#pattern> ) (object  ?rifand ))
)
)
(not
(exists
(TripleTemplate (subject  ?superimply ) (predicate  <http://www.w3.org/2007/rif#if> ) (object  ?rifand ))
)
)
(not
(exists
(and
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?superand ))
(TripleTemplate (subject  ?superand ) (predicate  <http://www.w3.org/2007/rif#formulas> ) (object  ?formulalist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?formulalist   ?rifand  ))

)
)
)
	=>
 (bind ?clipsand   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifand ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>))))(assert(TripleTemplate (subject  ?rifand ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?clipsand )))(assert(Member (instance  ?clipsand ) (class  <http://clips.script/AndCE> )))(assert(TripleTemplate (subject  ?clipsand ) (predicate  <http://clips.script/conditional-element> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>)))))

(defrule rule96 (declare (salience -10))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#add-pattern-from> ) (object  ?rifframe ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?slotvalue ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?frameobject ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#formulalist> ) (object  ?formulalist ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?slotkey ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?slotlist  ))

(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

(not
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?slot ))
)
(not
(exists
(and
(TripleTemplate (subject  ?slot ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#constraints-needs-variable> ) (object  ?x ))
(not
(TripleTemplate (subject  ?slot ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?x ))
)
)
)
)
(not
(exists
(and
(TripleTemplate (subject  ?frameobject ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#constraint-needs-variable> ) (object  ?x ))
(not
(TripleTemplate (subject  ?slot ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?x ))
)
)
)
)
	=>
(assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?slot )))(assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?rifframe ))) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?formulacontainer  )  (eq ?fct1:predicate   <http://white.gobo/local/b/ncfe8f320_n6144#formulalist>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?formulalist   ?slot  ))))(assert(Member (instance  ?slot ) (class  <http://white.gobo/modelA#TripleTemplateGenerator> )))(assert(TripleTemplate (subject  ?slot ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#transfer-variable-binding> ) (object  ?formulacontainer )))(assert(Member (instance  ?rifframe ) (class  <http://white.gobo/modelA#TripleTemplateGenerator> )))(assert(TripleTemplate (subject  ?rifframe ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#transfer-variable-binding> ) (object  ?formulacontainer ))))

(defrule rule97 (declare (salience -10))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?targetiri ))
(TripleTemplate (subject  ?rifexternal ) (predicate  <http://www.w3.org/2007/rif#content> ) (object  ?rifatom ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/modelA#as-defrule> ) (object  ?defrule ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#add-pattern-from> ) (object  ?rifexternal ))
(TripleTemplate (subject  ?targetstring ) (predicate  <http://example.com/as-expression> ) (object  ?clipsassign ))
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?rifconstiristring ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#formulalist> ) (object  ?formulalist ))
(TripleTemplate (subject  ?rifconstiristring ) (predicate  <http://www.w3.org/2007/rif#constIRI> ) (object  "http%3A%2F%2Fwww.w3.org%2F2007%2Frif-builtin-predicate%23iri-string^^http://www.w3.org/2001/XMLSchema#anyURI" ))
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?rifexternal ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?arglist  ))

(test (eq ?targetstring   (<http://www.w3.org/2007/rif-builtin-function#get> ?arglist   "1^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

(test (eq ?targetiri   (<http://www.w3.org/2007/rif-builtin-function#get> ?arglist   "0^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

(not
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?rifexternal ))
)
(not
(TripleTemplate (subject  ?rifexternal ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?clipsassign ))
)
(not
(exists
(and
(TripleTemplate (subject  ?targetstring ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#expression-needs-var> ) (object  ?x ))
(not
(TripleTemplate (subject  ?rifexternal ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?x ))
)
)
)
)
	=>
(assert(Member (instance  ?rifexternal ) (class  <http://white.gobo/modelA#AssignGenerator> )))(assert(TripleTemplate (subject  ?targetiri ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#use-expression-from> ) (object  ?targetstring )))(assert(Member (instance  ?targetstring ) (class  <http://white.gobo/modelA#ExpressionGenerator> )))(assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?rifexternal )))(assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?targetstring ))))

(defrule rule98 (declare (salience 5))
(TripleTemplate (subject  ?rifnot ) (predicate  <http://www.w3.org/2007/rif#formula> ) (object  ?rifformula ))
(TripleTemplate (subject  ?rifnot ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?clipsvar ))
(not
(exists
(TripleTemplate (subject  ?rifnot ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?subpattern ))
)
)
(or
(Member (class  <http://www.w3.org/2007/rif#INeg> ) (instance  ?rifnot ))
(Member (class  <http://www.w3.org/2007/rif#Exists> ) (instance  ?rifnot ))
)
	=>
(assert(TripleTemplate (subject  ?rifformula ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?clipsvar ))))

(defrule rule99 (declare (salience 5))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-expression> ) (object  ?clipsexpression ))
(TripleTemplate (subject  ?rifterm ) (predicate  <http://example.com/inherits-data> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifterm ) (predicate  <http://www.w3.org/2007/rif#items> ) (object  ?itemlist ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifvar ))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?rifterm ))
(Atom (op  <http://white.gobo/local/b/ncfe8f320_n6144#check-binding> ) (args  ?rifterm ))
(not
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?itemlist   ?rifvar  ))

)
	=>
(assert(TripleTemplate (subject  ?rifterm ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#expression-needs-var> ) (object  ?clipsexpression ))))

(defrule rule100 (declare (salience 5))
(Member (class  <http://www.w3.org/2007/rif#Or> ) (instance  ?formula ))
	=>
 (bind ?clipsor   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>))))(assert(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?clipsor )))(assert(Member (instance  ?clipsor ) (class  <http://clips.script/OrCE> )))(assert(TripleTemplate (subject  ?clipsor ) (predicate  <http://clips.script/conditional-element> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>)))))

(defrule rule101 (declare (salience 5))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#constraint-binds-var> ) (object  ?clipsconstraint ))
(or
(TripleTemplate (subject  ?rifobj ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifobj ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifobj ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifobj ) (predicate  <http://www.w3.org/2007/rif#instance> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifobj ) (predicate  <http://www.w3.org/2007/rif#class> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifobj ) (predicate  <http://www.w3.org/2007/rif#sub> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifobj ) (predicate  <http://www.w3.org/2007/rif#super> ) (object  ?rifvar ))
)
(not
(TripleTemplate (subject  ?rifobj ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?clipsconstraint ))
)
(or
(Member (class  <http://white.gobo/modelA#MemberPatternGenerator> ) (instance  ?rifobj ))
(Member (class  <http://white.gobo/modelA#TripleTemplateGenerator> ) (instance  ?rifobj ))
(Member (class  <http://white.gobo/modelA#SubclassPatternGenerator> ) (instance  ?rifobj ))
)
	=>
(assert(TripleTemplate (subject  ?rifobj ) (predicate  <http://white.gobo/modelA#binds-var> ) (object  ?clipsconstraint ))))

(defrule rule102 (declare (salience -10))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?riflist ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#expression-needs-var> ) (object  ?unboundvar ))
(Member (class  <http://white.gobo/modelA#ConstraintGenerator> ) (instance  ?riflist ))
(not
(TripleTemplate (subject  ?riflist ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?unboundvar ))
)
(not
(Member (class  <http://white.gobo/modelA#ExpressionGenerator> ) (instance  ?riflist ))
)
	=>
(assert(Member (instance  ?riflist ) (class  <http://white.gobo/modelA#ListAsConstraint> ))))

(defrule rule103 (declare (salience 5))
(TripleTemplate (subject  ?term ) (predicate  <http://example.com/inherits-data> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-expression> ) (object  ?clipsvar ))
(Member (class  <http://white.gobo/modelA#ConditionGenerator> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifvar ))
(or
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?term ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?term ))
)
	=>
(assert(TripleTemplate (subject  ?term ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#expression-needs-var> ) (object  ?clipsvar ))))

(defrule rule104 (declare (salience 11))
(Member (class  <http://white.gobo/modelA#PatternGenerator> ) (instance  ?pattern ))
(TripleTemplate (subject  ?pattern ) (predicate  <http://example.com/inherits-data> ) (object  ?term ))
(TripleTemplate (subject  ?term ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsvar ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?term ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?pattern ))
	=>
(assert(TripleTemplate (subject  ?term ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#expression-needs-var> ) (object  ?clipsvar ))))

(defrule rule105 (declare (salience 5))
(or
(TripleTemplate (subject  ?rifobj ) (predicate  <http://www.w3.org/2007/rif#pattern> ) (object  ?formula ))
(TripleTemplate (subject  ?rifobj ) (predicate  <http://www.w3.org/2007/rif#if> ) (object  ?formula ))
(TripleTemplate (subject  ?rifobj ) (predicate  <http://www.w3.org/2007/rif#formula> ) (object  ?formula ))
)
	=>
(assert(TripleTemplate (subject  ?rifobj ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#add-pattern-from> ) (object  ?formula ))))

(defrule rule106 (declare (salience 5))
(TripleTemplate (subject  ?riflist ) (predicate  <http://www.w3.org/2007/rif#rest> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#constraint-binds-var> ) (object  ?clipsconstraint ))
(Member (class  <http://white.gobo/modelA#ConstraintGenerator> ) (instance  ?riflist ))
	=>
(assert(TripleTemplate (subject  ?riflist ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#constraint-binds-var> ) (object  ?clipsconstraint ))))

(defrule rule107 (declare (salience 5))
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?superformula ))
(TripleTemplate (subject  ?superformula ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#add-pattern-from> ) (object  ?subformula ))
(TripleTemplate (subject  ?superformula ) (predicate  <http://white.gobo/modelA#binds-var> ) (object  ?clipsvar ))
(not
(TripleTemplate (subject  ?superformula ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?subformula ))
)
	=>
(assert(TripleTemplate (subject  ?subformula ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?clipsvar ))))

(defrule rule108 (declare (salience 5))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifvar ))
(TripleTemplate (subject  ?rifexpression ) (predicate  <http://example.com/as-expression> ) (object  ?clipsexpression ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#use-expression-from> ) (object  ?rifexpression ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-expression> ) (object  ?clipsvar ))
	=>
(assert(TripleTemplate (subject  ?clipsvar ) (predicate  <http://clips.script/var-as-const-expr> ) (object  ?clipsexpression ))))

(defrule rule109 (declare (salience 5))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#constraint-needs-var> ) (object  ?clipsvar ))
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?arglist   ?rifvar  ))

	=>
(assert(TripleTemplate (subject  ?rifatom ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#constraints-needs-variable> ) (object  ?clipsvar ))))

(defrule rule110 (declare (salience 5))
(TripleTemplate (subject  ?subformula ) (predicate  <http://white.gobo/modelA#binds-var> ) (object  ?clipsconstraint ))
(TripleTemplate (subject  ?rifand ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?subformula ))
(TripleTemplate (subject  ?rifand ) (predicate  <http://www.w3.org/2007/rif#formulas> ) (object  ?formulalist ))
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?rifand ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?formulalist   ?subformula  ))

	=>
(assert(TripleTemplate (subject  ?rifand ) (predicate  <http://white.gobo/modelA#binds-var> ) (object  ?clipsconstraint ))))

(defrule rule111 (declare (salience 5))
(TripleTemplate (subject  ?rifexternal ) (predicate  <http://www.w3.org/2007/rif#content> ) (object  ?rifatom ))
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
(TripleTemplate (subject  ?arg ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#expression-needs-var> ) (object  ?clipsvar ))
(Member (class  <http://white.gobo/modelA#PatternGenerator> ) (instance  ?rifexternal ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?rifexternal ))
(or
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?arg ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?arg ))
)
	=>
(assert(TripleTemplate (subject  ?rifexternal ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#constraints-needs-variable> ) (object  ?clipsvar ))))

(defrule rule112 (declare (salience -12))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#formulalist> ) (object  ?formulalist ))
(TripleTemplate (subject  ?rifequal ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?rifleft ))
(TripleTemplate (subject  ?rifequal ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?rifright ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/modelA#as-defrule> ) (object  ?defrule ))
(TripleTemplate (subject  ?rifright ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsassign ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#add-pattern-from> ) (object  ?rifequal ))
(Member (class  <http://www.w3.org/2007/rif#Equal> ) (instance  ?rifequal ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifright ))
(not
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?rifequal ))
)
(not
(TripleTemplate (subject  ?rifequal ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?clipsassign ))
)
(not
(exists
(and
(TripleTemplate (subject  ?rifleft ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#expression-needs-var> ) (object  ?x ))
(not
(TripleTemplate (subject  ?rifequal ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?x ))
)
)
)
)
	=>
(assert(TripleTemplate (subject  ?rifequal ) (predicate  <http://white.gobo/modelA#binds-var> ) (object  ?clipsassign )))(assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?rifequal )))(assert(Member (instance  ?rifequal ) (class  <http://white.gobo/modelA#TestPatternRightAssignGenerator> )))(assert(Member (instance  ?rifequal ) (class  <http://white.gobo/modelA#PatternGenerator> )))(assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?clipsassign ))))

(defrule rule113 (declare (salience 5))
(TripleTemplate (subject  ?rifor ) (predicate  <http://www.w3.org/2007/rif#formulas> ) (object  ?formulalist ))
(TripleTemplate (subject  ?firstsubformula ) (predicate  <http://white.gobo/modelA#binds-var> ) (object  ?clipsconstraint ))
(Member (class  <http://www.w3.org/2007/rif#Or> ) (instance  ?rifor ))
(test (eq ?firstsubformula   (<http://www.w3.org/2007/rif-builtin-function#get> ?formulalist   "0^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

(not
(exists
(and
(Member (class  <http://white.gobo/local/b/ncfe8f320_n6144#rifformula> ) (instance  ?otherformula ))
(not
(TripleTemplate (subject  ?otherformula ) (predicate  <http://white.gobo/modelA#binds-var> ) (object  ?clipsconstraint ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?formulalist   ?otherformula  ))

)
)
)
	=>
(assert(TripleTemplate (subject  ?rifor ) (predicate  <http://white.gobo/modelA#binds-var> ) (object  ?clipsconstraint ))))

(defrule rule114 (declare (salience -1))
(TripleTemplate (subject  ?andpattern ) (predicate  <http://clips.script/conditional-element> ) (object  ?conditions ))
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#lhs-pattern-after-conditions> ) (object  ?aftercondition ))
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#transfer-after-conditions> ) (object  ?andpattern ))
(not
(TripleTemplate (subject  ?aftercondition ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#transferred-after-condition> ) (object  ?andpattern ))
)
	=>
(assert(TripleTemplate (subject  ?aftercondition ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#transferred-after-condition> ) (object  ?andpattern ))) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?andpattern  )  (eq ?fct1:predicate   <http://clips.script/conditional-element>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?andpattern ) (predicate  <http://clips.script/conditional-element> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?conditions   ?aftercondition  )))))

(defrule rule115 (declare (salience -10))
(Member (class  <http://white.gobo/modelA#ConditionGenerator> ) (instance  ?rifexternal ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#add-pattern-from> ) (object  ?rifexternal ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#formulalist> ) (object  ?formulalist ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?rifexternal ))
(not
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?rifexternal ))
)
(not
(exists
(and
(TripleTemplate (subject  ?rifexternal ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#expressions-needs-var> ) (object  ?x ))
(not
(TripleTemplate (subject  ?rifexternal ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?x ))
)
)
)
)
	=>
(assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?rifexternal ))) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?formulacontainer  )  (eq ?fct1:predicate   <http://white.gobo/local/b/ncfe8f320_n6144#formulalist>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?formulalist   ?rifexternal  ))))(assert(Member (instance  ?rifexternal ) (class  <http://white.gobo/modelA#TestPatternExternalGenerator> )))(assert(Member (instance  ?rifexternal ) (class  <http://white.gobo/modelA#PatternGenerator> ))))

(defrule rule116 (declare (salience 5))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#constraint-binds-var> ) (object  ?clipsconstraint ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(Member (class  <http://white.gobo/modelA#PatternGenerator> ) (instance  ?rifframe ))
(Member (class  <http://www.w3.org/2007/rif#Slot> ) (instance  ?slot ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

(not
(TripleTemplate (subject  ?rifframe ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?clipsconstraint ))
)
(or
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?rifvar ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?rifvar ))
)
	=>
(assert(TripleTemplate (subject  ?rifframe ) (predicate  <http://white.gobo/modelA#binds-var> ) (object  ?clipsconstraint ))))

(defrule rule117 (declare (salience -10))
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?rifatom ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#add-pattern-from> ) (object  ?rifatom ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#formulalist> ) (object  ?formulalist ))
(not
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?rifatom ))
)
(not
(exists
(and
(TripleTemplate (subject  ?rifatom ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#constraints-needs-variable> ) (object  ?x ))
(not
(TripleTemplate (subject  ?rifatom ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?x ))
)
)
)
)
	=>
(assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?rifatom ))) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?formulacontainer  )  (eq ?fct1:predicate   <http://white.gobo/local/b/ncfe8f320_n6144#formulalist>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?formulalist   ?rifatom  ))))(assert(Member (instance  ?rifatom ) (class  <http://white.gobo/modelA#AtomPatternGenerator> )))(assert(Member (instance  ?rifatom ) (class  <http://white.gobo/modelA#PatternGenerator> ))))

(defrule rule118 (declare (salience 11))
(TripleTemplate (subject  ?rifvarconsumer ) (predicate  <http://example.com/as-expression> ) (object  ?clipsvar ))
(TripleTemplate (subject  ?rifineg ) (predicate  <http://example.com/inherits-data> ) (object  ?rifvarconsumer ))
(Member (class  <http://www.w3.org/2007/rif#INeg> ) (instance  ?rifineg ))
	=>
(assert(TripleTemplate (subject  ?rifineg ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#constraints-needs-variable> ) (object  ?clipsvar ))))

(defrule rule119 (declare (salience 20))
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?otherrifand ))
(TripleTemplate (subject  ?otherrifand ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#add-pattern-from> ) (object  ?rifformula ))
(TripleTemplate (subject  ?rifand ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#add-pattern-from> ) (object  ?otherrifand ))
(or
(Member (class  <http://www.w3.org/2007/rif#Not> ) (instance  ?rifand ))
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?rifand ))
)
	=>
(assert(TripleTemplate (subject  ?otherrifand ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?rifformula )))(assert(TripleTemplate (subject  ?rifand ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?otherrifand )))(assert(TripleTemplate (subject  ?rifand ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#add-pattern-from> ) (object  ?rifformula ))))

(defrule rule120 (declare (salience 5))
(TripleTemplate (subject  ?riflist ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#expression-needs-var> ) (object  ?unboundvar ))
(Member (class  <http://white.gobo/modelA#ListAsConstraint> ) (instance  ?riflist ))
(not
(TripleTemplate (subject  ?riflist ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?unboundvar ))
)
	=>
(assert(TripleTemplate (subject  ?riflist ) (predicate  <http://white.gobo/modelA#binds-var> ) (object  ?unboundvar ))))

(defrule rule121 (declare (salience 5))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
(Member (class  <http://white.gobo/modelA#ConditionGenerator> ) (instance  ?parent ))
(or
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?x ))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?x ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?x ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?arglist   ?x  ))

	=>
(assert(Atom (op  <http://white.gobo/local/b/ncfe8f320_n6144#check-binding> ) (args  ?x ))))

(defrule rule122 (declare (salience -100))
(TripleTemplate (subject  ?rif ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#add-pattern-from> ) (object  ?pattern ))
(not
(TripleTemplate (subject  ?rif ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?pattern ))
)
	=>
(assert(Member (instance  ?pattern ) (class  <http://example.com/misses-bound-variables> )))(assert(TripleTemplate (subject  ?rif ) (predicate  <http://example.com/misses-pattern-for> ) (object  ?pattern ))) (<http://white.gobo/set-graph-in-errorstate> "Dont%20know%20where%20to%20add%20pattern%20for%20a%20formula%28ex%3Amisses-bound-variables%29"  ))

(defrule rule123 (declare (salience 5))
(Member (class  <http://white.gobo/modelA#ConditionGenerator> ) (instance  ?x ))
	=>
(assert(Atom (op  <http://white.gobo/local/b/ncfe8f320_n6144#check-binding> ) (args  ?x ))))

(defrule rule124 (declare (salience -1))
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#as-multi-lhs-pattern> ) (object  ?subpattern ))
(TripleTemplate (subject  ?superpattern ) (predicate  <http://clips.script/conditional-element> ) (object  ?patternlist ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#formulalist> ) (object  ?formulalist ))
(Member (class  <http://white.gobo/modelA#MultiPatternGenerator> ) (instance  ?formula ))
(test (eq ?formula   (<http://www.w3.org/2007/rif-builtin-function#get> ?formulalist   "0^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

(or
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/modelA#as-defrule> ) (object  ?superpattern ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?superpattern ))
)
(or
(Member (class  <http://clips.script/Defrule> ) (instance  ?superpattern ))
(Member (class  <http://clips.script/NotCE> ) (instance  ?superpattern ))
(Member (class  <http://clips.script/OrCE> ) (instance  ?superpattern ))
(Member (class  <http://clips.script/ExistsCE> ) (instance  ?superpattern ))
(Member (class  <http://clips.script/AndCE> ) (instance  ?superpattern ))
)
	=>
 (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?formulacontainer  )  (eq ?fct1:predicate   <http://white.gobo/local/b/ncfe8f320_n6144#formulalist>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#remove> ?formulalist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )))) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?superpattern  )  (eq ?fct1:predicate   <http://clips.script/conditional-element>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?superpattern ) (predicate  <http://clips.script/conditional-element> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?patternlist   ?subpattern  ))))(assert(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#transfer-variable-binding> ) (object  ?formulacontainer ))))

(defrule rule125 (declare (salience -12))
(TripleTemplate (subject  ?rifleft ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsassign ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#formulalist> ) (object  ?formulalist ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#add-pattern-from> ) (object  ?rifequal ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/modelA#as-defrule> ) (object  ?defrule ))
(TripleTemplate (subject  ?rifequal ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?rifright ))
(TripleTemplate (subject  ?rifequal ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?rifleft ))
(Member (class  <http://www.w3.org/2007/rif#Equal> ) (instance  ?rifequal ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifleft ))
(not
(TripleTemplate (subject  ?rifequal ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?clipsassign ))
)
(not
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?rifequal ))
)
(not
(exists
(and
(TripleTemplate (subject  ?rifright ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#expression-needs-var> ) (object  ?x ))
(not
(TripleTemplate (subject  ?rifequal ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?x ))
)
)
)
)
	=>
(assert(TripleTemplate (subject  ?rifequal ) (predicate  <http://white.gobo/modelA#binds-var> ) (object  ?clipsassign )))(assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?rifequal )))(assert(Member (instance  ?rifequal ) (class  <http://white.gobo/modelA#TestPatternLeftAssignGenerator> )))(assert(Member (instance  ?rifequal ) (class  <http://white.gobo/modelA#PatternGenerator> )))(assert(Member (instance  ?rifright ) (class  <http://white.gobo/modelA#ExpressionGenerator> )))(assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?clipsassign ))))

(defrule rule126 (declare (salience 5))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsconstraint ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifvar ))
	=>
(assert(TripleTemplate (subject  ?rifvar ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#constraint-binds-var> ) (object  ?clipsconstraint ))))

(defrule rule127 (declare (salience 5))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#constraint-binds-var> ) (object  ?clipsconstraint ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://www.w3.org/2007/rif#items> ) (object  ?itemlist ))
(Member (class  <http://white.gobo/modelA#ConstraintGenerator> ) (instance  ?riflist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?itemlist   ?rifvar  ))

	=>
(assert(TripleTemplate (subject  ?riflist ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#constraint-binds-var> ) (object  ?clipsconstraint ))))

(defrule rule128 (declare (salience 5))
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#binds-var> ) (object  ?clipsvar ))
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#transfer-variable-binding> ) (object  ?formulacontainer ))
	=>
(assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?clipsvar ))))

(defrule rule129 (declare (salience 5))
(or
(TripleTemplate (subject  ?rifrule ) (predicate  <http://www.w3.org/2007/rif#then> ) (object  ?rifaction ))
(and
(TripleTemplate (subject  ?rifrule ) (predicate  <http://www.w3.org/2007/rif#formula> ) (object  ?rifaction ))
(Member (class  <http://www.w3.org/2007/rif#Forall> ) (instance  ?rifrule ))
)
)
	=>
(assert(TripleTemplate (subject  ?rifrule ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#add-as-action> ) (object  ?rifaction ))))

(defrule rule130 (declare (salience 5))
(TripleTemplate (subject  ?atom ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#content> ) (object  ?atom ))
(Member (class  <http://white.gobo/modelA#ConditionGenerator> ) (instance  ?parent ))
(or
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?x ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?x ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?x ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?arglist   ?x  ))

	=>
(assert(Atom (op  <http://white.gobo/local/b/ncfe8f320_n6144#check-binding> ) (args  ?x ))))

(defrule rule131 (declare (salience 11))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-expression> ) (object  ?clipsvar ))
(TripleTemplate (subject  ?formula ) (predicate  <http://example.com/inherits-data> ) (object  ?rifvar ))
(TripleTemplate (subject  ?formula ) (predicate  <http://www.w3.org/2007/rif#vars> ) (object  ?varlist ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifvar ))
(Member (class  <http://www.w3.org/2007/rif#Exists> ) (instance  ?formula ))
	=>
(assert(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#constraints-needs-variable> ) (object  ?clipsvar ))))

(defrule rule132 (declare (salience -10))
(TripleTemplate (subject  ?superpattern ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#add-pattern-from> ) (object  ?subpattern ))
(TripleTemplate (subject  ?superpattern ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#formulalist> ) (object  ?formulalist ))
(not
(TripleTemplate (subject  ?superpattern ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?subpattern ))
)
(not
(exists
(and
(TripleTemplate (subject  ?subpattern ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#constraints-needs-variable> ) (object  ?x ))
(not
(TripleTemplate (subject  ?superpattern ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?x ))
)
)
)
)
(not
(exists
(and
(TripleTemplate (subject  ?subpattern ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#add-pattern-from> ) (object  ?subsub ))
(not
(TripleTemplate (subject  ?subpattern ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?subsub ))
)
)
)
)
(or
(Member (class  <http://www.w3.org/2007/rif#INeg> ) (instance  ?subpattern ))
(Member (class  <http://www.w3.org/2007/rif#Exists> ) (instance  ?subpattern ))
)
	=>
(assert(TripleTemplate (subject  ?superpattern ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?subpattern ))) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?superpattern  )  (eq ?fct1:predicate   <http://white.gobo/local/b/ncfe8f320_n6144#formulalist>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?superpattern ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?formulalist   ?subpattern  )))))

(defrule rule133 (declare (salience 5))
(TripleTemplate (subject  ?super ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#add-as-action> ) (object  ?sub ))
(TripleTemplate (subject  ?sub ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#add-as-action> ) (object  ?rifaction ))
	=>
(assert(TripleTemplate (subject  ?super ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#add-as-action> ) (object  ?rifaction ))))

(defrule rule134 (declare (salience 5))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsvar ))
(Member (class  <http://white.gobo/modelA#SubclassPatternGenerator> ) (instance  ?rifsubclass ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifvar ))
(or
(TripleTemplate (subject  ?rifsubclass ) (predicate  <http://www.w3.org/2007/rif#sub> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifsubclass ) (predicate  <http://www.w3.org/2007/rif#super> ) (object  ?rifvar ))
)
	=>
(assert(Member (instance  ?clipsvar ) (class  <http://example.com/Variable> ))))

(defrule rule135 (declare (salience 5))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?clipsvar ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#add-pattern-from> ) (object  ?formula ))
(not
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?formula ))
)
(or
(Member (class  <http://www.w3.org/2007/rif#Forall> ) (instance  ?formulacontainer ))
(Member (class  <http://www.w3.org/2007/rif#Implies> ) (instance  ?formulacontainer ))
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?formulacontainer ))
)
	=>
(assert(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?clipsvar ))))

(defrule rule136 (declare (salience -10))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#formulalist> ) (object  ?formulalist ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#add-pattern-from> ) (object  ?rifmember ))
(Member (class  <http://www.w3.org/2007/rif#Member> ) (instance  ?rifmember ))
(not
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?rifmember ))
)
(not
(exists
(and
(TripleTemplate (subject  ?rifmember ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#constraints-needs-variable> ) (object  ?x ))
(not
(TripleTemplate (subject  ?rifmember ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?x ))
)
)
)
)
	=>
(assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?rifmember ))) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?formulacontainer  )  (eq ?fct1:predicate   <http://white.gobo/local/b/ncfe8f320_n6144#formulalist>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?formulalist   ?rifmember  ))))(assert(Member (instance  ?rifmember ) (class  <http://white.gobo/modelA#MemberPatternGenerator> )))(assert(Member (instance  ?rifmember ) (class  <http://white.gobo/modelA#PatternGenerator> ))))

(defrule rule137 (declare (salience 5))
(TripleTemplate (subject  ?rifrule ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#add-as-action> ) (object  ?rifaction ))
(not
(Member (class  <http://www.w3.org/2007/rif#Implies> ) (instance  ?rifaction ))
)
(not
(Member (class  <http://www.w3.org/2007/rif#Forall> ) (instance  ?rifaction ))
)
	=>
(assert(Member (instance  ?rifaction ) (class  <http://white.gobo/modelA#ActionGenerator> ))))

(defrule rule138 (declare (salience 5))
(Member (class  <http://white.gobo/modelA#TripleTemplateGenerator> ) (instance  ?rifframe ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsvar ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifvar ))
(or
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?rifvar ))
)
	=>
(assert(Member (instance  ?clipsvar ) (class  <http://example.com/Variable> ))))

(defrule rule139 (declare (salience -10))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#add-pattern-from> ) (object  ?rifmember ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#formulalist> ) (object  ?formulalist ))
(Member (class  <http://www.w3.org/2007/rif#Subclass> ) (instance  ?rifmember ))
(not
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?rifmember ))
)
(not
(exists
(and
(TripleTemplate (subject  ?rifmember ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#constraints-needs-variable> ) (object  ?x ))
(not
(TripleTemplate (subject  ?rifmember ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?x ))
)
)
)
)
	=>
(assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?rifmember ))) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?formulacontainer  )  (eq ?fct1:predicate   <http://white.gobo/local/b/ncfe8f320_n6144#formulalist>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?formulalist   ?rifmember  ))))(assert(Member (instance  ?rifmember ) (class  <http://white.gobo/modelA#SubclassPatternGenerator> )))(assert(Member (instance  ?rifmember ) (class  <http://white.gobo/modelA#PatternGenerator> ))))

(defrule rule140 (declare (salience 5))
(TripleTemplate (subject  ?rifand ) (predicate  <http://www.w3.org/2007/rif#formulas> ) (object  ?formulalist ))
(or
(Member (class  <http://white.gobo/local/b/ncfe8f320_n6144#rifformula> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#Member> ) (instance  ?formula ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?formulalist   ?formula  ))

(or
(Member (class  <http://www.w3.org/2007/rif#Or> ) (instance  ?rifand ))
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?rifand ))
)
	=>
(assert(TripleTemplate (subject  ?rifand ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#add-pattern-from> ) (object  ?formula ))))

(defrule rule141 (declare (salience 5))
(Member (class  <http://white.gobo/modelA#AtomPatternGenerator> ) (instance  ?rifobj ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#constraint-binds-var> ) (object  ?clipsconstraint ))
(TripleTemplate (subject  ?rifobj ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?rifvar ))
(not
(TripleTemplate (subject  ?rifobj ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?clipsconstraint ))
)
	=>
(assert(TripleTemplate (subject  ?rifobj ) (predicate  <http://white.gobo/modelA#binds-var> ) (object  ?clipsconstraint ))))

(defrule rule142 (declare (salience 5))
(TripleTemplate (subject  ?rifrule ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#add-as-action> ) (object  ?rifaction ))
(TripleTemplate (subject  ?rifrule ) (predicate  <http://white.gobo/modelA#as-defrule> ) (object  ?defrule ))
(or
(TripleTemplate (subject  ?rifaction ) (predicate  <http://example.com/as-action> ) (object  ?clipsaction ))
(TripleTemplate (subject  ?rifaction ) (predicate  <http://white.gobo/modelA#as-action> ) (object  ?clipsaction ))
)
	=>
(assert(TripleTemplate (subject  ?defrule ) (predicate  <http://clips.script/action> ) (object  ?clipsaction ))))

(defrule rule143 (declare (salience 5))
(TripleTemplate (subject  ?rifexternal ) (predicate  <http://www.w3.org/2007/rif#content> ) (object  ?rifatom ))
(TripleTemplate (subject  ?arg ) (predicate  <http://example.com/as-expression> ) (object  ?clipsvar ))
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?rifexternal ))
(Member (class  <http://white.gobo/modelA#PatternGenerator> ) (instance  ?rifexternal ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?arg ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?arglist   ?arg  ))

	=>
(assert(TripleTemplate (subject  ?rifexternal ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#constraints-needs-variable> ) (object  ?clipsvar ))))

(defrule rule144 (declare (salience 5))
(Member (class  <http://white.gobo/modelA#PatternGenerator> ) (instance  ?rifformula ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#constraint-binds-var> ) (object  ?clipsconstraint ))
(not
(TripleTemplate (subject  ?rifformula ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?clipsconstraint ))
)
(or
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#super> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#class> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#sub> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#instance> ) (object  ?rifvar ))
)
	=>
(assert(TripleTemplate (subject  ?rifformula ) (predicate  <http://white.gobo/modelA#binds-var> ) (object  ?clipsconstraint ))))

(defrule rule145 (declare (salience 5))
(TripleTemplate (subject  ?expression ) (predicate  <http://example.com/inherits-data> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-expression> ) (object  ?clipsvar ))
(Member (class  <http://white.gobo/modelA#ExpressionGenerator> ) (instance  ?expression ))
(Member (class  <http://clips.script/Variable> ) (instance  ?clipsvar ))
(Atom (op  <http://white.gobo/local/b/ncfe8f320_n6144#always-wrong> ) (args ))
(not
(Member (class  <http://example.com/ConstraintGenerator> ) (instance  ?clipsvar ))
)
	=>
(assert(TripleTemplate (subject  ?expression ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#expression-needs-var> ) (object  ?clipsvar ))))

(defrule rule146 (declare (salience 5))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#constraint-binds-var> ) (object  ?clipsconstraint ))
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
(Member (class  <http://white.gobo/modelA#PatternGenerator> ) (instance  ?rifatom ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?arglist   ?rifvar  ))

(not
(TripleTemplate (subject  ?rifatom ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?clipsconstraint ))
)
	=>
(assert(TripleTemplate (subject  ?rifatom ) (predicate  <http://white.gobo/modelA#binds-var> ) (object  ?clipsconstraint ))))

(defrule rule147 (declare (salience 20))
(TripleTemplate (subject  ?rifforall ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#add-pattern-from> ) (object  ?rifrule ))
(TripleTemplate (subject  ?rifrule ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#add-pattern-from> ) (object  ?rifformula ))
(or
(Member (class  <http://www.w3.org/2007/rif#Implies> ) (instance  ?rifrule ))
(Member (class  <http://www.w3.org/2007/rif#Forall> ) (instance  ?rifrule ))
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?rifrule ))
)
(or
(Member (class  <http://www.w3.org/2007/rif#Implies> ) (instance  ?rifforall ))
(Member (class  <http://www.w3.org/2007/rif#Forall> ) (instance  ?rifforall ))
)
	=>
(assert(TripleTemplate (subject  ?rifrule ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?rifformula )))(assert(TripleTemplate (subject  ?rifforall ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?rifrule )))(assert(TripleTemplate (subject  ?rifforall ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#add-pattern-from> ) (object  ?rifformula ))))

(defrule rule148 (declare (salience 5))
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?rifrule ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?clipsconstraint ))
(TripleTemplate (subject  ?rifrule ) (predicate  <http://www.w3.org/2007/rif#formulas> ) (object  ?formulalist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?formulalist   ?rifformula  ))

(or
(Member (class  <http://www.w3.org/2007/rif#Equal> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#Member> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?rifformula ))
)
	=>
(assert(TripleTemplate (subject  ?rifformula ) (predicate  <http://white.gobo/modelA#bound-variable> ) (object  ?clipsconstraint ))))

(defrule rule149 (declare (salience 5))
(Member (class  <http://www.w3.org/2007/rif#Exists> ) (instance  ?formula ))
	=>
 (bind ?clipsexists   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>))))(assert(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?clipsexists )))(assert(Member (instance  ?clipsexists ) (class  <http://clips.script/ExistsCE> )))(assert(TripleTemplate (subject  ?clipsexists ) (predicate  <http://clips.script/conditional-element> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>)))))

(defrule rule150 (declare (salience 5))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifvar ))
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsvar ))
(Member (class  <http://white.gobo/modelA#AtomPatternGenerator> ) (instance  ?rifatom ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?arglist   ?rifvar  ))

	=>
(assert(Member (instance  ?clipsvar ) (class  <http://example.com/Variable> ))))

(defrule rule151 (declare (salience 5))
(Member (class  <http://white.gobo/modelA#ConditionGenerator> ) (instance  ?parent ))
(or
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#super> ) (object  ?term ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?term ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#subject> ) (object  ?term ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#sub> ) (object  ?term ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?term ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?term ))
)
	=>
(assert(Atom (op  <http://white.gobo/local/b/ncfe8f320_n6144#check-binding> ) (args  ?term ))))

(defrule rule152 (declare (salience -10))
(TripleTemplate (subject  ?rifequal ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?rifleft ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#formulalist> ) (object  ?formulalist ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#add-pattern-from> ) (object  ?rifequal ))
(TripleTemplate (subject  ?rifequal ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?rifright ))
(Member (class  <http://www.w3.org/2007/rif#Equal> ) (instance  ?rifequal ))
(Member (class  <http://white.gobo/modelA#ConditionGenerator> ) (instance  ?rifequal ))
(not
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?rifequal ))
)
(not
(exists
(and
(TripleTemplate (subject  ?rifright ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#expression-needs-var> ) (object  ?x ))
(not
(TripleTemplate (subject  ?rifequal ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?x ))
)
)
)
)
(not
(exists
(and
(TripleTemplate (subject  ?rifleft ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#expression-needs-var> ) (object  ?x ))
(not
(TripleTemplate (subject  ?rifequal ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?x ))
)
)
)
)
	=>
(assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#added-pattern-from> ) (object  ?rifequal ))) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?formulacontainer  )  (eq ?fct1:predicate   <http://white.gobo/local/b/ncfe8f320_n6144#formulalist>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?formulalist   ?rifequal  ))))(assert(Member (instance  ?rifequal ) (class  <http://white.gobo/modelA#TestPatternEqualGenerator> )))(assert(Member (instance  ?rifequal ) (class  <http://white.gobo/modelA#PatternGenerator> )))(assert(Member (instance  ?rifleft ) (class  <http://white.gobo/modelA#ExpressionGenerator> )))(assert(Member (instance  ?rifright ) (class  <http://white.gobo/modelA#ExpressionGenerator> ))))

(defrule rule153 (declare (salience 5))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#constraint-binds-var> ) (object  ?clipsconstraint ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://www.w3.org/2007/rif#items> ) (object  ?itemlist ))
(Member (class  <http://example.com/ConstraintGenerator> ) (instance  ?riflist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?itemlist   ?rifvar  ))

	=>
(assert(TripleTemplate (subject  ?rifvar ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#constraint-binds-var> ) (object  ?clipsconstraint ))))

(defrule rule154 (declare (salience 5))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#constraint-needs-var> ) (object  ?clipsvar ))
(or
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#content> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#sub> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#super> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#class> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#instance> ) (object  ?rifvar ))
)
	=>
(assert(TripleTemplate (subject  ?rifformula ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#constraints-needs-variable> ) (object  ?clipsvar ))))

(defrule rule155 (declare (salience 5))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifvar ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-expression> ) (object  ?clipsexpression ))
(Atom (op  <http://white.gobo/local/b/ncfe8f320_n6144#check-binding> ) (args  ?rifvar ))
	=>
(assert(TripleTemplate (subject  ?rifvar ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#expression-needs-var> ) (object  ?clipsexpression ))))

(defrule rule156 (declare (salience 5))
(TripleTemplate (subject  ?group ) (predicate  <http://www.w3.org/2007/rif#sentences> ) (object  ?sentences ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?sentences  ))

(or
(Member (class  <http://www.w3.org/2007/rif#Forall> ) (instance  ?rifrule ))
(Member (class  <http://www.w3.org/2007/rif#Implies> ) (instance  ?rifrule ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?sentences   ?rifrule  ))

	=>
 (bind ?defrule   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifrule ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>))))(assert(TripleTemplate (subject  ?rifrule ) (predicate  <http://white.gobo/modelA#as-defrule> ) (object  ?defrule )))(assert(Member (instance  ?defrule ) (class  <http://clips.script/Defrule> )))(assert(TripleTemplate (subject  ?defrule ) (predicate  <http://clips.script/conditional-element> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>)))))

(defrule rule157 (declare (salience 5))
(Member (class  <http://white.gobo/modelA#MemberPatternGenerator> ) (instance  ?rifmember ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsvar ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifvar ))
(or
(TripleTemplate (subject  ?rifmember ) (predicate  <http://www.w3.org/2007/rif#class> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifmember ) (predicate  <http://www.w3.org/2007/rif#instance> ) (object  ?rifvar ))
)
	=>
(assert(Member (instance  ?clipsvar ) (class  <http://example.com/Variable> ))))

(defrule rule158 (declare (salience -10))
(Member (class  <http://white.gobo/modelA#ConstraintGenerator> ) (instance  ?riflist ))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?riflist ))
(not
(exists
(TripleTemplate (subject  ?riflist ) (predicate  <http://www.w3.org/2007/rif#rest> ) (object  ?rest ))
)
)
(not
(Member (class  <http://white.gobo/modelA#ListAsConstraint> ) (instance  ?riflist ))
)
(not
(exists
(and
(TripleTemplate (subject  ?riflist ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#expression-needs-var> ) (object  ?x ))
(not
(TripleTemplate (subject  ?riflist ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#bound-variable> ) (object  ?x ))
)
)
)
)
	=>
(assert(Member (instance  ?riflist ) (class  <http://white.gobo/modelA#ExpressionGenerator> ))))

(defrule rule159 (declare (salience 11))
(TripleTemplate (subject  ?rifexternal ) (predicate  <http://example.com/inherits-data> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-expression> ) (object  ?clipsvar ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifvar ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?rifexternal ))
(Member (class  <http://white.gobo/modelA#ConditionGenerator> ) (instance  ?rifexternal ))
	=>
(assert(TripleTemplate (subject  ?rifexternal ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#expressions-needs-var> ) (object  ?clipsvar ))))

(defrule rule160 (declare (salience -1))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#formulalist> ) (object  ?formulalist ))
(TripleTemplate (subject  ?superpattern ) (predicate  <http://clips.script/conditional-element> ) (object  ?patternlist ))
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?subpattern ))
(test (eq ?formula   (<http://www.w3.org/2007/rif-builtin-function#get> ?formulalist   "0^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

(exists
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#lhs-pattern-after-conditions> ) (object  ?x ))
)
(or
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?superpattern ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/modelA#as-defrule> ) (object  ?superpattern ))
)
(or
(Member (class  <http://clips.script/NotCE> ) (instance  ?superpattern ))
(Member (class  <http://clips.script/AndCE> ) (instance  ?superpattern ))
(Member (class  <http://clips.script/OrCE> ) (instance  ?superpattern ))
(Member (class  <http://clips.script/Defrule> ) (instance  ?superpattern ))
(Member (class  <http://clips.script/ExistsCE> ) (instance  ?superpattern ))
)
	=>
 (bind ?andpattern   (<http://white.gobo/new-blanknode>) )(assert(Member (instance  ?andpattern ) (class  <http://clips.script/AndCE> )))(assert(TripleTemplate (subject  ?andpattern ) (predicate  <http://clips.script/conditional-element> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?subpattern  ))))(assert(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#transfer-after-conditions> ) (object  ?andpattern ))) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?formulacontainer  )  (eq ?fct1:predicate   <http://white.gobo/local/b/ncfe8f320_n6144#formulalist>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#remove> ?formulalist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )))) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?superpattern  )  (eq ?fct1:predicate   <http://clips.script/conditional-element>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?superpattern ) (predicate  <http://clips.script/conditional-element> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?patternlist   ?andpattern  ))))(assert(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#transfer-variable-binding> ) (object  ?formulacontainer ))))

(defrule rule161 (declare (salience -100))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#formulalist> ) (object  ?formulalist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#numeric-greater-than> (<http://www.w3.org/2007/rif-builtin-function#count> ?formulalist  )  "0^^http://www.w3.org/2001/XMLSchema#integer"  ))

	=>
(assert(Member (instance  (<http://www.w3.org/2007/rif-builtin-function#get> ?formulalist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )) (class  <http://example.com/couldnt-translate-to-pattern> )))(assert(Member (instance  ?formulacontainer ) (class  <http://example.com/missing-translated-pattern> ))) (<http://white.gobo/set-graph-in-errorstate> "Couldnt%20translate%20formula%20to%20pattern.%28ex%3Acouldnt-translate-to-pattern%20ex%3Amissing-translated-pattern%29"  ))

(defrule rule162 (declare (salience 5))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(Member (class  <http://white.gobo/modelA#ConditionGenerator> ) (instance  ?parent ))
(or
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?x ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?x ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

	=>
(assert(Atom (op  <http://white.gobo/local/b/ncfe8f320_n6144#check-binding> ) (args  ?x ))))

(defrule rule163 (declare (salience 5))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-expression> ) (object  ?clipsexpression ))
(TripleTemplate (subject  ?rifterm ) (predicate  <http://example.com/inherits-data> ) (object  ?rifvar ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifvar ))
(Atom (op  <http://white.gobo/local/b/ncfe8f320_n6144#check-binding> ) (args  ?rifterm ))
(not
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?rifterm ))
)
	=>
(assert(TripleTemplate (subject  ?rifterm ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#constraint-needs-var> ) (object  ?clipsexpression )))(assert(TripleTemplate (subject  ?rifterm ) (predicate  <http://white.gobo/local/b/ncfe8f320_n6144#expression-needs-var> ) (object  ?clipsexpression ))))

(defrule rule164
(TripleTemplate (subject  ?group ) (predicate  <http://www.w3.org/2007/rif#sentences> ) (object  ?sentences ))
(TripleTemplate (subject  ?group ) (predicate  <http://example.com/combine-deffacts-in> ) (object  ?deffacts ))
(TripleTemplate (subject  ?factable ) (predicate  <http://example.com/as-rhspattern> ) (object  ?newrhspattern ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?sentences  ))

(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?sentences   ?factable  ))

(or
(Member (class  <http://www.w3.org/2007/rif#Member> ) (instance  ?factable ))
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?factable ))
(Member (class  <http://www.w3.org/2007/rif#Subclass> ) (instance  ?factable ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?factable ))
)
	=>
 (bind ?rhspatternlist   (do-for-fact (( ?fcct8 TripleTemplate)) (and (eq ?fcct8:subject   ?deffacts  )  (eq ?fcct8:predicate   <http://clips.script/rhs-pattern>  ) ) (fact-slot-value ?fcct8   object  ) )  ) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?deffacts  )  (eq ?fct1:predicate   <http://clips.script/rhs-pattern>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?deffacts ) (predicate  <http://clips.script/rhs-pattern> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?rhspatternlist   ?newrhspattern  )))))

(defrule rule165
(TripleTemplate (subject  ?group ) (predicate  <http://www.w3.org/2007/rif#sentences> ) (object  ?sentences ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?sentences  ))

(exists
(and
(or
(Member (class  <http://www.w3.org/2007/rif#Member> ) (instance  ?factable ))
(Member (class  <http://www.w3.org/2007/rif#Subclass> ) (instance  ?factable ))
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?factable ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?factable ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?sentences   ?factable  ))

)
)
	=>
 (bind ?deffacts   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?group ) (predicate  <http://example.com/combine-deffacts-in> ) (object  ?deffacts )))(assert(Member (instance  ?deffacts ) (class  <http://clips.script/Deffacts> )))(assert(TripleTemplate (subject  ?deffacts ) (predicate  <http://clips.script/rhs-pattern> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>)))))

(defrule rule166 (declare (salience 10))
(TripleTemplate (subject  ?rifop ) (predicate  <http://example.com/as-expression> ) (object  ?functionsymbol ))
(TripleTemplate (subject  ?functionsymbol ) (predicate  <http://clips.script/symbol> ) (object  ?functionname ))
(TripleTemplate (subject  ?rifexternal ) (predicate  <http://www.w3.org/2007/rif#content> ) (object  ?content ))
(TripleTemplate (subject  ?content ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?rifarglist ))
(TripleTemplate (subject  ?content ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?rifop ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?rifexternal ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?rifarglist  ))

	=>
 (bind ?function   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifexternal ) (predicate  <http://example.com/as-action> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?function  ))))(assert(TripleTemplate (subject  ?rifexternal ) (predicate  <http://example.com/as-expression> ) (object  ?function )))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-name> ) (object  ?functionname )))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>))))(assert(TripleTemplate (subject  ?function ) (predicate  <http://example.com/add-args-from> ) (object  ?rifarglist ))))

(defrule rule167 (declare (salience -50))
(TripleTemplate (subject  ?function ) (predicate  <http://example.com/add-args-from> ) (object  ?rifarglist ))
(not
(test (eq "0^^http://www.w3.org/2001/XMLSchema#integer"   (<http://www.w3.org/2007/rif-builtin-function#count> ?rifarglist  ) ))

)
	=>
(assert(Member (instance  ?function ) (class  <http://example.com/didnt-translate-all-args> ))) (<http://white.gobo/set-graph-in-errorstate> "Didnt%20translate%20all%20arguments%20for%20function%28ex%3Adidnt-translate-all-args%29"  ))

(defrule rule168
(Member (class  <http://white.gobo/modelA#TestPatternExternalGenerator> ) (instance  ?rifexternal ))
	=>
(assert(Member (instance  ?rifexternal ) (class  <http://white.gobo/modelA#ExpressionGenerator> ))))

(defrule rule169
(TripleTemplate (subject  ?rifexternal ) (predicate  <http://example.com/as-expression> ) (object  ?action ))
(Member (class  <http://white.gobo/modelA#TestPatternExternalGenerator> ) (instance  ?rifexternal ))
	=>
 (bind ?pattern   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifexternal ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?pattern )))(assert(Member (instance  ?pattern ) (class  <http://clips.script/TestCE> )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/function-call> ) (object  ?action ))))

(defrule rule170 (declare (salience 15))
(TripleTemplate (subject  ?function ) (predicate  <http://example.com/add-args-from> ) (object  ?rifarglist ))
(TripleTemplate (subject  ?firstarg ) (predicate  <http://example.com/as-expression> ) (object  ?clipsexpression ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?rifarglist  ))

(test (eq ?firstarg   (<http://www.w3.org/2007/rif-builtin-function#get> ?rifarglist   "0^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

	=>
 (bind ?functionargs   (do-for-fact (( ?fcct9 TripleTemplate)) (and (eq ?fcct9:subject   ?function  )  (eq ?fcct9:predicate   <http://clips.script/function-args>  ) ) (fact-slot-value ?fcct9   object  ) )  ) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?function  )  (eq ?fct1:predicate   <http://clips.script/function-args>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?functionargs   ?clipsexpression  )))) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?function  )  (eq ?fct1:predicate   <http://example.com/add-args-from>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?function ) (predicate  <http://example.com/add-args-from> ) (object  (<http://www.w3.org/2007/rif-builtin-function#remove> ?rifarglist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )))))

(defrule rule171
(Member (class  <http://white.gobo/modelA#SubclassPatternGenerator> ) (instance  ?rifmember ))
(TripleTemplate (subject  ?rifmember ) (predicate  <http://www.w3.org/2007/rif#super> ) (object  ?rifsuper ))
(TripleTemplate (subject  ?rifsuper ) (predicate  <http://example.com/as-constraint> ) (object  ?constraintsuper ))
(TripleTemplate (subject  ?rifmember ) (predicate  <http://www.w3.org/2007/rif#sub> ) (object  ?rifsub ))
(TripleTemplate (subject  ?rifsub ) (predicate  <http://example.com/as-constraint> ) (object  ?constraintsub ))
(not
(exists
(TripleTemplate (subject  ?rifmember ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?x ))
)
)
	=>
 (bind ?slotsuper   (<http://white.gobo/new-blanknode>) ) (bind ?slotsub   (<http://white.gobo/new-blanknode>) ) (bind ?pattern   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifmember ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?pattern )))(assert(Member (instance  ?pattern ) (class  <http://clips.script/TemplatePatternCE> )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/deftemplate-name> ) (object  "Subclass" )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/slot> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?slotsuper   ?slotsub  ))))(assert(TripleTemplate (subject  ?slotsuper ) (predicate  <http://clips.script/slot-name> ) (object  "super" )))(assert(TripleTemplate (subject  ?slotsuper ) (predicate  <http://clips.script/constraint> ) (object  ?constraintsuper )))(assert(TripleTemplate (subject  ?slotsub ) (predicate  <http://clips.script/slot-name> ) (object  "sub" )))(assert(TripleTemplate (subject  ?slotsub ) (predicate  <http://clips.script/constraint> ) (object  ?constraintsub ))))

(defrule rule172 (declare (salience 100))
(TripleTemplate (subject  ?patterngen ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
(Member (class  <http://white.gobo/modelA#RHSPatternGenerator> ) (instance  ?patterngen ))
(or
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?term ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?term ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?arglist   ?term  ))

	=>
(assert(Member (instance  ?term ) (class  <http://white.gobo/modelA#ExpressionGenerator> ))))

(defrule rule173 (declare (salience 100))
(or
(Member (class  <http://www.w3.org/2007/rif#Modify> ) (instance  ?action ))
(Member (class  <http://www.w3.org/2007/rif#Assert> ) (instance  ?action ))
(Member (class  <http://www.w3.org/2007/rif#Retract> ) (instance  ?action ))
(Member (class  <http://www.w3.org/2007/rif#Execute> ) (instance  ?action ))
)
	=>
(assert(Member (instance  ?action ) (class  <http://white.gobo/modelA#ActionGenerator> ))))

(defrule rule174 (declare (salience 100))
(TripleTemplate (subject  ?rifimply ) (predicate  <http://www.w3.org/2007/rif#then> ) (object  ?action ))
	=>
(assert(Member (instance  ?action ) (class  <http://white.gobo/modelA#ActionGenerator> ))))

(defrule rule175 (declare (salience 100))
(or
(TripleTemplate (subject  ?rifimply ) (predicate  <http://www.w3.org/2007/rif#if> ) (object  ?formula ))
(TripleTemplate (subject  ?rifimply ) (predicate  <http://www.w3.org/2007/rif#pattern> ) (object  ?formula ))
)
	=>
(assert(Member (instance  ?formula ) (class  <http://white.gobo/modelA#ConditionGenerator> ))))

(defrule rule176 (declare (salience 100))
(Member (class  <http://white.gobo/modelA#RHSPatternGenerator> ) (instance  ?patterngen ))
(or
(TripleTemplate (subject  ?patterngen ) (predicate  <http://www.w3.org/2007/rif#instance> ) (object  ?term ))
(TripleTemplate (subject  ?patterngen ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?term ))
(TripleTemplate (subject  ?patterngen ) (predicate  <http://www.w3.org/2007/rif#class> ) (object  ?term ))
(TripleTemplate (subject  ?patterngen ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?term ))
(TripleTemplate (subject  ?patterngen ) (predicate  <http://www.w3.org/2007/rif#super> ) (object  ?term ))
(TripleTemplate (subject  ?patterngen ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?term ))
(TripleTemplate (subject  ?patterngen ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?term ))
(TripleTemplate (subject  ?patterngen ) (predicate  <http://www.w3.org/2007/rif#sub> ) (object  ?term ))
(TripleTemplate (subject  ?patterngen ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?term ))
(TripleTemplate (subject  ?patterngen ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?term ))
)
	=>
(assert(Member (instance  ?term ) (class  <http://white.gobo/modelA#ExpressionGenerator> ))))

(defrule rule177 (declare (salience 100))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(Member (class  <http://www.w3.org/2007/rif#Slot> ) (instance  ?slot ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

(Member (class  <http://white.gobo/modelA#ConditionGenerator> ) (instance  ?rifformula ))
	=>
(assert(Member (instance  ?slot ) (class  <http://white.gobo/modelA#ConditionGenerator> ))))

(defrule rule178 (declare (salience 100))
(Member (class  <http://white.gobo/modelA#RHSPatternGenerator> ) (instance  ?rifframe ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(Member (class  <http://www.w3.org/2007/rif#Slot> ) (instance  ?slot ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

	=>
(assert(Member (instance  ?slot ) (class  <http://white.gobo/modelA#RHSPatternGenerator> ))))

(defrule rule179 (declare (salience 100))
(Member (class  <http://white.gobo/modelA#PatternGenerator> ) (instance  ?rifformula ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://white.gobo/modelA#pattern-uses-constraint> ) (object  ?superlist ))
(TripleTemplate (subject  ?superlist ) (predicate  <http://www.w3.org/2007/rif#items> ) (object  ?itemlist ))
(or
(Member (class  <http://www.w3.org/2007/rif#Variable> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?child ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?itemlist   ?child  ))

	=>
(assert(Member (instance  ?child ) (class  <http://white.gobo/modelA#ConstraintGenerator> )))(assert(TripleTemplate (subject  ?rifformula ) (predicate  <http://white.gobo/modelA#pattern-uses-constraint> ) (object  ?child ))))

(defrule rule180 (declare (salience 100))
(TripleTemplate (subject  ?clause ) (predicate  <http://www.w3.org/2007/rif#then> ) (object  ?assert ))
(or
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?assert ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?assert ))
(Member (class  <http://www.w3.org/2007/rif#Member> ) (instance  ?assert ))
)
	=>
(assert(Member (instance  ?assert ) (class  <http://white.gobo/modelA#RHSPatternGenerator> ))))

(defrule rule181 (declare (salience 100))
(Member (class  <http://white.gobo/modelA#ConditionGenerator> ) (instance  ?formula ))
(TripleTemplate (subject  ?formula ) (predicate  <http://www.w3.org/2007/rif#formulas> ) (object  ?formulalist ))
(or
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Or> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#INeg> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Exists> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Equal> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#SubClass> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Member> ) (instance  ?child ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?formulalist   ?child  ))

	=>
(assert(Member (instance  ?child ) (class  <http://white.gobo/modelA#ConditionGenerator> ))))

(defrule rule182 (declare (salience 100))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
(Member (class  <http://white.gobo/modelA#PatternGenerator> ) (instance  ?rifformula ))
(or
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Variable> ) (instance  ?child ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?arglist   ?child  ))

	=>
(assert(Member (instance  ?child ) (class  <http://white.gobo/modelA#ConstraintGenerator> )))(assert(TripleTemplate (subject  ?rifformula ) (predicate  <http://white.gobo/modelA#pattern-uses-constraint> ) (object  ?child ))))

(defrule rule183 (declare (salience 100))
(TripleTemplate (subject  ?riflist ) (predicate  <http://www.w3.org/2007/rif#items> ) (object  ?arglist ))
(Member (class  <http://white.gobo/modelA#ExpressionGenerator> ) (instance  ?riflist ))
(or
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?term ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?term ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?arglist   ?term  ))

	=>
(assert(Member (instance  ?term ) (class  <http://white.gobo/modelA#ExpressionGenerator> ))))

(defrule rule184 (declare (salience 100))
(Member (class  <http://www.w3.org/2007/rif#Forall> ) (instance  ?rifforall ))
(TripleTemplate (subject  ?rifforall ) (predicate  <http://www.w3.org/2007/rif#formula> ) (object  ?action ))
(not
(Member (class  <http://www.w3.org/2007/rif#Implies> ) (instance  ?action ))
)
(not
(Member (class  <http://www.w3.org/2007/rif#Forall> ) (instance  ?action ))
)
	=>
(assert(Member (instance  ?action ) (class  <http://white.gobo/modelA#ActionGenerator> ))))

(defrule rule185 (declare (salience 100))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?child ))
(Member (class  <http://white.gobo/modelA#AtomPatternGenerator> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?child ))
	=>
(assert(Member (instance  ?rifformula ) (class  <http://white.gobo/modelA#MultiPatternGenerator> ))))

(defrule rule186 (declare (salience 100))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?child ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
(Member (class  <http://white.gobo/modelA#AtomPatternGenerator> ) (instance  ?rifformula ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?arglist   ?child  ))

	=>
(assert(Member (instance  ?rifformula ) (class  <http://white.gobo/modelA#MultiPatternGenerator> ))))

(defrule rule187 (declare (salience 100))
(Member (class  <http://www.w3.org/2007/rif#Slot> ) (instance  ?slot ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?child ))
(Member (class  <http://white.gobo/modelA#TripleTemplateGenerator> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?child ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

	=>
(assert(Member (instance  ?slot ) (class  <http://white.gobo/modelA#MultiPatternGenerator> ))))

(defrule rule188 (declare (salience 100))
(Member (class  <http://white.gobo/modelA#ConditionGenerator> ) (instance  ?formula ))
(TripleTemplate (subject  ?formula ) (predicate  <http://www.w3.org/2007/rif#formula> ) (object  ?child ))
	=>
(assert(Member (instance  ?child ) (class  <http://white.gobo/modelA#ConditionGenerator> ))))

(defrule rule189 (declare (salience 100))
(Member (class  <http://white.gobo/modelA#PatternGenerator> ) (instance  ?rifformula ))
(or
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?child ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?child ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#class> ) (object  ?child ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?child ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?child ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?child ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?child ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#sub> ) (object  ?child ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#instance> ) (object  ?child ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#super> ) (object  ?child ))
)
	=>
(assert(Member (instance  ?child ) (class  <http://white.gobo/modelA#ConstraintGenerator> )))(assert(TripleTemplate (subject  ?rifformula ) (predicate  <http://white.gobo/modelA#pattern-uses-constraint> ) (object  ?child ))))

(defrule rule190 (declare (salience 100))
(TripleTemplate (subject  ?group ) (predicate  <http://www.w3.org/2007/rif#sentences> ) (object  ?sentences ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?sentences  ))

(or
(Member (class  <http://www.w3.org/2007/rif#Equal> ) (instance  ?rifclause ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?sentences   ?rifclause  ))

	=>
(assert(Member (instance  ?rifclause ) (class  <http://example.com/equal-not-implemented-as-clause> ))) (<http://white.gobo/set-graph-in-errorstate> "modelA%20cant%20process%20rif%3AEqual%20as%20clause%28ex%3Aequal-not-implemented-as-clause%29"  ))

(defrule rule191 (declare (salience 100))
(Member (class  <http://white.gobo/modelA#ConditionGenerator> ) (instance  ?rifformula ))
(or
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?rifformula ))
)
	=>
(assert(Member (instance  ?rifformula ) (class  <http://white.gobo/modelA#PatternGenerator> ))))

(defrule rule192 (declare (salience 100))
(TripleTemplate (subject  ?action ) (predicate  <http://www.w3.org/2007/rif#target> ) (object  ?target ))
(or
(Member (class  <http://www.w3.org/2007/rif#Retract> ) (instance  ?action ))
(Member (class  <http://www.w3.org/2007/rif#Modify> ) (instance  ?action ))
(Member (class  <http://www.w3.org/2007/rif#Assert> ) (instance  ?action ))
)
	=>
(assert(Member (instance  ?target ) (class  <http://white.gobo/modelA#RHSPatternGenerator> ))))

(defrule rule193 (declare (salience 100))
(TripleTemplate (subject  ?group ) (predicate  <http://www.w3.org/2007/rif#sentences> ) (object  ?sentences ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?sentences  ))

(or
(Member (class  <http://www.w3.org/2007/rif#Subclass> ) (instance  ?rifclause ))
(Member (class  <http://www.w3.org/2007/rif#Member> ) (instance  ?rifclause ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?rifclause ))
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?rifclause ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?sentences   ?rifclause  ))

	=>
(assert(Member (instance  ?rifclause ) (class  <http://white.gobo/modelA#RHSPatternGenerator> ))))

(defrule rule194 (declare (salience 100))
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
(TripleTemplate (subject  ?rifexternal ) (predicate  <http://www.w3.org/2007/rif#content> ) (object  ?rifatom ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?rifexternal ))
(Member (class  <http://white.gobo/modelA#ExpressionGenerator> ) (instance  ?rifexternal ))
(or
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?child ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?arglist   ?child  ))

	=>
(assert(Member (instance  ?child ) (class  <http://white.gobo/modelA#ExpressionGenerator> ))))

(defrule rule195 (declare (salience 100))
(TripleTemplate (subject  ?group ) (predicate  <http://www.w3.org/2007/rif#sentences> ) (object  ?sentences ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?sentences  ))

(or
(Member (class  <http://www.w3.org/2007/rif#Implies> ) (instance  ?rifrule ))
(Member (class  <http://www.w3.org/2007/rif#Forall> ) (instance  ?rifrule ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?sentences   ?rifrule  ))

	=>
(assert(Member (instance  ?rifrule ) (class  <http://white.gobo/modelA#RuleGenerator> ))))

(defrule rule196
(TripleTemplate (subject  ?items ) (predicate  <http://white.gobo/local/b/ncfe8f320_n1666#add-additional-patterns-to> ) (object  ?multipattern ))
(TripleTemplate (subject  ?items ) (predicate  <http://clips.script/constraints> ) (object  ?oldlist ))
(TripleTemplate (subject  ?items ) (predicate  <http://white.gobo/local/b/ncfe8f320_n1666#add-item-from> ) (object  ?rifitems ))
(TripleTemplate (subject  ?item ) (predicate  <http://example.com/as-constraint> ) (object  ?term ))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?item ))
(test (eq ?item   (<http://www.w3.org/2007/rif-builtin-function#get> ?rifitems   "0^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

	=>
 (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?items  )  (eq ?fct1:predicate   <http://white.gobo/local/b/ncfe8f320_n1666#add-item-from>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?items ) (predicate  <http://white.gobo/local/b/ncfe8f320_n1666#add-item-from> ) (object  (<http://www.w3.org/2007/rif-builtin-function#remove> ?rifitems   "0^^http://www.w3.org/2001/XMLSchema#integer"  )))) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?items  )  (eq ?fct1:predicate   <http://clips.script/constraints>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?items ) (predicate  <http://clips.script/constraints> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?oldlist   ?term  ))))(assert(TripleTemplate (subject  ?multipattern ) (predicate  <http://white.gobo/local/b/ncfe8f320_n1666#add-list> ) (object  ?item ))))

(defrule rule197
(TripleTemplate (subject  ?items ) (predicate  <http://white.gobo/local/b/ncfe8f320_n1666#add-item-from> ) (object  ?rifitems ))
(TripleTemplate (subject  ?items ) (predicate  <http://clips.script/constraints> ) (object  ?oldlist ))
(TripleTemplate (subject  ?item ) (predicate  <http://example.com/as-constraint> ) (object  ?term ))
(test (eq ?item   (<http://www.w3.org/2007/rif-builtin-function#get> ?rifitems   "0^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

(or
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?item ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?item ))
(Member (class  <http://www.w3.org/2007/rif#Const> ) (instance  ?item ))
)
	=>
 (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?items  )  (eq ?fct1:predicate   <http://white.gobo/local/b/ncfe8f320_n1666#add-item-from>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?items ) (predicate  <http://white.gobo/local/b/ncfe8f320_n1666#add-item-from> ) (object  (<http://www.w3.org/2007/rif-builtin-function#remove> ?rifitems   "0^^http://www.w3.org/2001/XMLSchema#integer"  )))) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?items  )  (eq ?fct1:predicate   <http://clips.script/constraints>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?items ) (predicate  <http://clips.script/constraints> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?oldlist   ?term  )))))

(defrule rule198
(TripleTemplate (subject  ?items ) (predicate  <http://white.gobo/local/b/ncfe8f320_n1666#use-items-from> ) (object  ?list ))
(TripleTemplate (subject  ?list ) (predicate  <http://www.w3.org/2007/rif#rest> ) (object  ?rest ))
(TripleTemplate (subject  ?items ) (predicate  <http://white.gobo/local/b/ncfe8f320_n1666#add-item-from> ) (object  ?rifitems ))
(TripleTemplate (subject  ?items ) (predicate  <http://clips.script/constraints> ) (object  ?oldlist ))
(test (eq "0^^http://www.w3.org/2001/XMLSchema#integer"   (<http://www.w3.org/2007/rif-builtin-function#count> ?rifitems  ) ))

(not
(Member (class  <http://white.gobo/local/b/ncfe8f320_n1666#OpenList> ) (instance  ?items ))
)
(not
(test (eq ?rest   (<http://www.w3.org/2007/rif-builtin-function#make-list>) ))

)
	=>
 (bind ?anyslots   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?items ) (predicate  <http://white.gobo/local/b/ncfe8f320_n1666#added-rest> ) (object  ?rest )))(assert(Member (instance  ?anyslots ) (class  <http://clips.script/MultifieldVariable> )))(assert(TripleTemplate (subject  ?anyslots ) (predicate  <http://clips.script/variable-name> ) (object  "" ))) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?items  )  (eq ?fct1:predicate   <http://clips.script/constraints>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?items ) (predicate  <http://clips.script/constraints> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?oldlist   ?anyslots  ))))(assert(Member (instance  ?items ) (class  <http://white.gobo/local/b/ncfe8f320_n1666#OpenList> ))))

(defrule rule199
(Member (class  <http://white.gobo/modelA#MultiPatternGenerator> ) (instance  ?formula ))
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?formulapattern ))
(Member (class  <http://white.gobo/modelA#AtomPatternGenerator> ) (instance  ?formula ))
	=>
 (bind ?andpattern   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#as-multi-lhs-pattern> ) (object  ?andpattern )))(assert(Member (instance  ?andpattern ) (class  <http://clips.script/AndCE> )))(assert(TripleTemplate (subject  ?andpattern ) (predicate  <http://clips.script/conditional-element> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?formulapattern  )))))

(defrule rule200
(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/as-constraint> ) (object  ?listvar ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://www.w3.org/2007/rif#items> ) (object  ?itemlist ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://www.w3.org/2007/rif#rest> ) (object  ?rest ))
(TripleTemplate (subject  ?multipattern ) (predicate  <http://white.gobo/local/b/ncfe8f320_n1666#add-list> ) (object  ?riflist ))
(TripleTemplate (subject  ?rest ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsvar ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rest ))
(not
(Member (class  <http://white.gobo/modelA#VarAsConstExpr> ) (instance  ?clipsvar ))
)
(not
(Member (class  <http://example.com/Variable> ) (instance  ?clipsvar ))
)
	=>
 (bind ?position   (<http://white.gobo/new-blanknode>) ) (bind ?function   (<http://white.gobo/new-blanknode>) )(assert(Member (instance  ?clipsvar ) (class  <http://white.gobo/modelA#VarAsConstExpr> )))(assert(TripleTemplate (subject  ?clipsvar ) (predicate  <http://clips.script/var-as-const-expr> ) (object  ?function )))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-name> ) (object  "%3Chttp%3A%2F%2Fwww.w3.org%2F2007%2Frif-builtin-function%23sublist%3E" )))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?listvar   ?position  ))))(assert(TripleTemplate (subject  ?position ) (predicate  <http://clips.script/string> ) (object  (<http://white.gobo/literal-to-clipsconstant> (<http://www.w3.org/2007/rif-builtin-function#count> ?itemlist  ) )))))

(defrule rule201
(TripleTemplate (subject  ?list ) (predicate  <http://www.w3.org/2007/rif#items> ) (object  ?rifitems ))
(TripleTemplate (subject  ?list ) (predicate  <http://example.com/as-constraint> ) (object  ?listvar ))
(TripleTemplate (subject  ?multipattern ) (predicate  <http://white.gobo/local/b/ncfe8f320_n1666#add-list> ) (object  ?list ))
(not
(TripleTemplate (subject  ?multipattern ) (predicate  <http://white.gobo/local/b/ncfe8f320_n1666#added-list> ) (object  ?list ))
)
	=>
 (bind ?checkvar   (<http://white.gobo/new-blanknode>) ) (bind ?pattern   (<http://white.gobo/new-blanknode>) ) (bind ?oldlist   (do-for-fact (( ?fcct10 TripleTemplate)) (and (eq ?fcct10:subject   ?multipattern  )  (eq ?fcct10:predicate   <http://clips.script/conditional-element>  ) ) (fact-slot-value ?fcct10   object  ) )  ) (bind ?check   (<http://white.gobo/new-blanknode>) ) (bind ?items   (<http://white.gobo/new-blanknode>) ) (bind ?assign   (<http://white.gobo/new-blanknode>) ) (bind ?checkfunction   (<http://white.gobo/new-blanknode>) )(assert(Member (instance  ?checkvar ) (class  <http://example.com/Variable> )))(assert(Member (instance  ?checkvar ) (class  <http://clips.script/Variable> )))(assert(Member (instance  ?assign ) (class  <http://clips.script/AssignedPatternCE> )))(assert(TripleTemplate (subject  ?assign ) (predicate  <http://clips.script/fact-var-symbol> ) (object  ?checkvar )))(assert(TripleTemplate (subject  ?assign ) (predicate  <http://clips.script/pattern-ce> ) (object  ?pattern )))(assert(Member (instance  ?pattern ) (class  <http://clips.script/TemplatePatternCE> )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/deftemplate-name> ) (object  "AtomList" )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/slot> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?items  ))))(assert(TripleTemplate (subject  ?items ) (predicate  <http://white.gobo/local/b/ncfe8f320_n1666#add-additional-patterns-to> ) (object  ?multipattern )))(assert(TripleTemplate (subject  ?items ) (predicate  <http://clips.script/slot-name> ) (object  "items" )))(assert(TripleTemplate (subject  ?items ) (predicate  <http://clips.script/constraints> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>))))(assert(TripleTemplate (subject  ?items ) (predicate  <http://white.gobo/local/b/ncfe8f320_n1666#add-item-from> ) (object  ?rifitems )))(assert(TripleTemplate (subject  ?items ) (predicate  <http://white.gobo/local/b/ncfe8f320_n1666#use-items-from> ) (object  ?list )))(assert(Member (instance  ?check ) (class  <http://clips.script/TestCE> )))(assert(TripleTemplate (subject  ?check ) (predicate  <http://clips.script/function-call> ) (object  ?checkfunction )))(assert(TripleTemplate (subject  ?checkfunction ) (predicate  <http://clips.script/function-name> ) (object  "eq" )))(assert(TripleTemplate (subject  ?checkfunction ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?checkvar   ?listvar  )))) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?multipattern  )  (eq ?fct1:predicate   <http://clips.script/conditional-element>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?multipattern ) (predicate  <http://clips.script/conditional-element> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?oldlist   ?assign   ?check  ))))(assert(TripleTemplate (subject  ?multipattern ) (predicate  <http://white.gobo/local/b/ncfe8f320_n1666#added-list> ) (object  ?list ))))

(defrule rule202
(TripleTemplate (subject  ?list ) (predicate  <http://www.w3.org/2007/rif#rest> ) (object  ?rest ))
(TripleTemplate (subject  ?rest ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsvar ))
(TripleTemplate (subject  ?multipattern ) (predicate  <http://white.gobo/local/b/ncfe8f320_n1666#add-list> ) (object  ?list ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://www.w3.org/2007/rif#items> ) (object  ?itemlist ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/as-expression> ) (object  ?listvar ))
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#as-multi-lhs-pattern> ) (object  ?multipattern ))
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#binds-var> ) (object  ?clipsvar ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rest ))
(or
(Member (class  <http://example.com/Variable> ) (instance  ?clipsvar ))
(Member (class  <http://white.gobo/modelA#VarAsConstExpr> ) (instance  ?clipsvar ))
)
	=>
 (bind ?position   (<http://white.gobo/new-blanknode>) ) (bind ?rightexpr   (<http://white.gobo/new-blanknode>) ) (bind ?leftexpr   (<http://white.gobo/new-blanknode>) ) (bind ?eq   (<http://white.gobo/new-blanknode>) ) (bind ?testpattern   (<http://white.gobo/new-blanknode>) )(assert(Member (instance  ?testpattern ) (class  <http://clips.script/TestCE> )))(assert(TripleTemplate (subject  ?testpattern ) (predicate  <http://clips.script/function-call> ) (object  ?eq )))(assert(TripleTemplate (subject  ?eq ) (predicate  <http://clips.script/function-name> ) (object  "eq" )))(assert(TripleTemplate (subject  ?eq ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?clipsvar   ?rightexpr  ))))(assert(TripleTemplate (subject  ?rightexpr ) (predicate  <http://clips.script/function-name> ) (object  "%3Chttp%3A%2F%2Fwww.w3.org%2F2007%2Frif-builtin-function%23sublist%3E" )))(assert(TripleTemplate (subject  ?rightexpr ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?listvar   ?position  ))))(assert(TripleTemplate (subject  ?position ) (predicate  <http://clips.script/string> ) (object  (<http://white.gobo/literal-to-clipsconstant> (<http://www.w3.org/2007/rif-builtin-function#count> ?itemlist  ) )))))

(defrule rule203
(TripleTemplate (subject  ?formula ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#as-multi-lhs-pattern> ) (object  ?andpattern ))
(Member (class  <http://white.gobo/modelA#MultiPatternGenerator> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?list ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?arglist   ?list  ))

(Member (class  <http://white.gobo/modelA#AtomPatternGenerator> ) (instance  ?formula ))
	=>
(assert(TripleTemplate (subject  ?andpattern ) (predicate  <http://white.gobo/local/b/ncfe8f320_n1666#add-list> ) (object  ?list ))))

(defrule rule204
(Member (class  <http://white.gobo/modelA#MultiPatternGenerator> ) (instance  ?formula ))
(TripleTemplate (subject  ?formula ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?list ))
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?formulapattern ))
(Member (class  <http://white.gobo/modelA#TripleTemplateGenerator> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?list ))
	=>
 (bind ?andpattern   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#as-multi-lhs-pattern> ) (object  ?andpattern )))(assert(Member (instance  ?andpattern ) (class  <http://clips.script/AndCE> )))(assert(TripleTemplate (subject  ?andpattern ) (predicate  <http://clips.script/conditional-element> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?formulapattern  ))))(assert(TripleTemplate (subject  ?andpattern ) (predicate  <http://white.gobo/local/b/ncfe8f320_n1666#add-list> ) (object  ?list ))))

(defrule rule205 (declare (salience 1000))
(TripleTemplate (subject  ?directive ) (predicate  <http://www.w3.org/2007/rif#profile> ) (object  ?profile ))
(TripleTemplate (subject  ?directive ) (predicate  <http://www.w3.org/2007/rif#location> ) (object  ?location ))
	=>
 (<http://white.gobo/import> ?location   ?profile  ))

(defrule rule206 (declare (salience 1000))
(TripleTemplate (subject  ?directive ) (predicate  <http://www.w3.org/2007/rif#location> ) (object  ?location ))
(not
(exists
(TripleTemplate (subject  ?directive ) (predicate  <http://www.w3.org/2007/rif#profile> ) (object  ?profile ))
)
)
	=>
(assert(TripleTemplate (subject  ?directive ) (predicate  <http://www.w3.org/2007/rif#profile> ) (object  <http://www.w3.org/ns/entailment/RIF> ))))

(defrule rule207 (declare (salience -1))
(Member (class  <http://example.com/Variable> ) (instance  ?factvar ))
(not
(exists
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/provides-expression> ) (object  ?factvar ))
)
)
(Atom (op  <http://example.com/currentfactindex> ) (args  ?factindex ))
(not
(exists
(TripleTemplate (subject  ?factvar ) (predicate  <http://clips.script/variable-name> ) (object  ?factname ))
)
)
(not
(exists
(and
(TripleTemplate (subject  ?othervar ) (predicate  <http://clips.script/variable-name> ) (object  ?tmpname ))
(test (eq ?tmpname   (<http://www.w3.org/2007/rif-builtin-function#concat> "fct"   ?factindex  ) ))

)
)
)
	=>
(assert(Member (instance  ?factvar ) (class  <http://clips.script/Variable> ))) (retract(assert(Atom (op  <http://example.com/currentfactindex> ) (args  ?factindex ))) )(assert(Atom (op  <http://example.com/currentfactindex> ) (args  (<http://www.w3.org/2007/rif-builtin-function#numeric-add> ?factindex   "1^^http://www.w3.org/2001/XMLSchema#integer"  ))))(assert(TripleTemplate (subject  ?factvar ) (predicate  <http://clips.script/variable-name> ) (object  (<http://www.w3.org/2007/rif-builtin-function#concat> "fct"   ?factindex  )))))

(defrule rule208
(TripleTemplate (subject  ?clipspattern ) (predicate  <http://clips.script/constraints> ) (object  ?constraintlist ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://www.w3.org/2007/rif#varname> ) (object  ?varname ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/provides-expression> ) (object  ?clipsvar ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?constraintlist   ?clipsvar  ))

	=>
(assert(Member (instance  ?clipsvar ) (class  <http://clips.script/Variable> )))(assert(TripleTemplate (subject  ?clipsvar ) (predicate  <http://clips.script/variable-name> ) (object  ?varname ))))

(defrule rule209
(TripleTemplate (subject  ?rifnode ) (predicate  <http://www.w3.org/2007/rif#constIRI> ) (object  ?iristring ))
	=>
 (bind ?clipsnode   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsnode )))(assert(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/as-expression> ) (object  ?clipsnode )))(assert(TripleTemplate (subject  ?clipsnode ) (predicate  <http://clips.script/symbol> ) (object  (<http://white.gobo/iri-to-clipsconstant> ?iristring  ))))(assert(TripleTemplate (subject  ?clipsnode ) (predicate  <http://example.com/as-constraint-needs-additional-conditionals> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>)))))

(defrule rule210
(TripleTemplate (subject  ?riflocal ) (predicate  <http://www.w3.org/2007/rif#constname> ) (object  ?name ))
(TripleTemplate (subject  ?rifdocument ) (predicate  <http://example.com/inherits-data> ) (object  ?riflocal ))
(Member (class  <http://www.w3.org/2007/rif#Document> ) (instance  ?rifdocument ))
	=>
 (bind ?clipsnode   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?riflocal ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsnode )))(assert(TripleTemplate (subject  ?riflocal ) (predicate  <http://example.com/as-expression> ) (object  ?clipsnode )))(assert(TripleTemplate (subject  ?clipsnode ) (predicate  <http://clips.script/symbol> ) (object  (<http://white.gobo/local-to-clipsconstant> ?rifdocument   ?name  )))))

(defrule rule211
(TripleTemplate (subject  ?rifvar ) (predicate  <http://www.w3.org/2007/rif#varname> ) (object  ?varname ))
(TripleTemplate (subject  ?rifdo ) (predicate  <http://www.w3.org/2007/rif#actionVar> ) (object  ?actionvar ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?actionvar   ?rifvar  ))

(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?actionvar  ))

	=>
 (bind ?clipsnode   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsnode )))(assert(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-expression> ) (object  ?clipsnode )))(assert(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/provides-expression> ) (object  ?clipsnode )))(assert(TripleTemplate (subject  ?clipsnode ) (predicate  <http://clips.script/variable-name> ) (object  ?varname )))(assert(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/inherits-data> ) (object  ?rifdo )))(assert(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/inherits-data> ) (object  (<http://www.w3.org/2007/rif-builtin-function#get> ?actionvar   "1^^http://www.w3.org/2001/XMLSchema#integer"  )))))

(defrule rule212 (declare (salience -1))
(Atom (op  <http://example.com/currentfactindex> ) (args  ?factindex ))
(exists
(and
(TripleTemplate (subject  ?othervar ) (predicate  <http://clips.script/variable-name> ) (object  ?tmpname ))
(test (eq ?tmpname   (<http://www.w3.org/2007/rif-builtin-function#concat> "fct"   ?factindex  ) ))

)
)
	=>
 (retract(assert(Atom (op  <http://example.com/currentfactindex> ) (args  ?factindex ))) )(assert(Atom (op  <http://example.com/currentfactindex> ) (args  (<http://www.w3.org/2007/rif-builtin-function#numeric-add> ?factindex   "1^^http://www.w3.org/2001/XMLSchema#integer"  )))))

(defrule rule213
(TripleTemplate (subject  ?rifvar ) (predicate  <http://www.w3.org/2007/rif#varname> ) (object  ?varname ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/provides-expression> ) (object  ?factvar ))
(Member (class  <http://example.com/Variable> ) (instance  ?factvar ))
(not
(exists
(TripleTemplate (subject  ?factvar ) (predicate  <http://clips.script/variable-name> ) (object  ?factname ))
)
)
	=>
(assert(Member (instance  ?factvar ) (class  <http://clips.script/Variable> )))(assert(TripleTemplate (subject  ?factvar ) (predicate  <http://clips.script/variable-name> ) (object  ?varname ))))

(defrule rule214 (declare (salience -1))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://example.com/as-expression> ) (object  ?factvar ))
(Member (class  <http://clips.script/Variable> ) (instance  ?factvar ))
(Atom (op  <http://example.com/currentfactindex> ) (args  ?factindex ))
(not
(exists
(TripleTemplate (subject  ?factvar ) (predicate  <http://clips.script/variable-name> ) (object  ?factname ))
)
)
(not
(exists
(and
(TripleTemplate (subject  ?othervar ) (predicate  <http://clips.script/variable-name> ) (object  ?tmpname ))
(test (eq ?tmpname   (<http://www.w3.org/2007/rif-builtin-function#concat> "fct"   ?factindex  ) ))

)
)
)
(or
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#Equal> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#Member> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#Subclass> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?rifformula ))
)
	=>
 (retract(assert(Atom (op  <http://example.com/currentfactindex> ) (args  ?factindex ))) )(assert(Atom (op  <http://example.com/currentfactindex> ) (args  (<http://www.w3.org/2007/rif-builtin-function#numeric-add> ?factindex   "1^^http://www.w3.org/2001/XMLSchema#integer"  ))))(assert(Member (instance  ?factvar ) (class  <http://clips.script/Variable> )))(assert(TripleTemplate (subject  ?factvar ) (predicate  <http://clips.script/variable-name> ) (object  (<http://www.w3.org/2007/rif-builtin-function#concat> "fct"   ?factindex  )))))

(defrule rule215
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifvar ))
(TripleTemplate (subject  ?rifforall ) (predicate  <http://www.w3.org/2007/rif#vars> ) (object  ?varlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?varlist   ?rifvar  ))

(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?varlist  ))

	=>
 (bind ?clipsnode   (<http://white.gobo/new-blanknode>) )(assert(Member (instance  ?clipsnode ) (class  <http://clips.script/Variable> )))(assert(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/provides-expression> ) (object  ?clipsnode )))(assert(TripleTemplate (subject  ?clipsnode ) (predicate  <http://example.com/as-constraint-needs-additional-conditionals> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>)))))

(deffacts factsd70fce0
(Atom (op  <http://example.com/currentfactindex> ) (args  "1^^http://www.w3.org/2001/XMLSchema#integer" ))
)

(defrule rule216 (declare (salience -100))
(TripleTemplate (subject  ?riflocal ) (predicate  <http://www.w3.org/2007/rif#constname> ) (object  ?name ))
(not
(exists
(and
(TripleTemplate (subject  ?rifdocument ) (predicate  <http://example.com/inherits-data> ) (object  ?riflocal ))
(Member (class  <http://www.w3.org/2007/rif#Document> ) (instance  ?rifdocument ))
)
)
)
	=>
(assert(Member (instance  ?riflocal ) (class  <http://white.gobo/modelA#missing-localterm> ))) (<http://white.gobo/set-graph-in-errorstate> "Missing%20connection%20of%20local%20constant%20to%20its%20document.%28modelA%3Amissing-localterm%29"  ))

(defrule rule217
(TripleTemplate (subject  ?rifnode ) (predicate  <http://www.w3.org/2007/rif#value> ) (object  ?value ))
	=>
 (bind ?clipsnode   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsnode )))(assert(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/as-expression> ) (object  ?clipsnode )))(assert(TripleTemplate (subject  ?clipsnode ) (predicate  <http://clips.script/string> ) (object  (<http://white.gobo/literal-to-clipsconstant> ?value  ))))(assert(TripleTemplate (subject  ?clipsnode ) (predicate  <http://example.com/as-constraint-needs-additional-conditionals> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>)))))

(defrule rule218
(TripleTemplate (subject  ?varparent ) (predicate  <http://example.com/provides-expression> ) (object  ?clipsvar ))
(TripleTemplate (subject  ?varparent ) (predicate  <http://www.w3.org/2007/rif#varname> ) (object  ?varname ))
(TripleTemplate (subject  ?varparent ) (predicate  <http://example.com/inherits-data> ) (object  ?varchild ))
(TripleTemplate (subject  ?varchild ) (predicate  <http://www.w3.org/2007/rif#varname> ) (object  ?varname ))
	=>
(assert(TripleTemplate (subject  ?varchild ) (predicate  <http://example.com/as-expression> ) (object  ?clipsvar )))(assert(TripleTemplate (subject  ?varchild ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsvar ))))

(defrule rule219 (declare (salience -102))
(Member (class  <http://clips.script/Variable> ) (instance  ?clipsvar ))
(not
(exists
(TripleTemplate (subject  ?clipsvar ) (predicate  <http://clips.script/variable-name> ) (object  ?varname ))
)
)
(not
(exists
(TripleTemplate (subject  ?clipsvar ) (predicate  <http://clips.script/var-as-const-expr> ) (object  ?varname ))
)
)
	=>
(assert(Member (instance  ?clipsvar ) (class  <http://white.gobo/modelA#missing-var-expression> ))) (<http://white.gobo/set-graph-in-errorstate> "A%20cs%3AVariable%20has%20no%20expression.%20missing%20cs%3Avariable-name%20or%20cs%3Avar-as-const-expr.%28modelA%3Amissing-var-expression%29"  ))

(defrule rule220 (declare (salience -100))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://www.w3.org/2007/rif#varname> ) (object  ?varname ))
(not
(exists
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-expression> ) (object  ?clipsnode ))
)
)
(not
(exists
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/provides-expression> ) (object  ?clipsnode ))
)
)
	=>
(assert(Member (instance  ?rifvar ) (class  <http://white.gobo/modelA#missing-var-binding> ))) (<http://white.gobo/set-graph-in-errorstate> (<http://www.w3.org/2007/rif-builtin-function#concat> "Missing%20binding%20for%20rif%3AVar%20with%20name%20"   ?varname   "%20%28modelA%3Amissing-var-binding%29.%20Might%20be%20missing%20mention%20of%20variable%20in%20rif%3AForall%20or%20rif%3AExists."  ) ))

(defrule rule221 (declare (salience -102))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/provides-expression> ) (object  ?clipsvar ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://www.w3.org/2007/rif#varname> ) (object  ?varname ))
(not
(exists
(TripleTemplate (subject  ?rifvarchild ) (predicate  <http://example.com/as-expression> ) (object  ?clipsvar ))
)
)
	=>
(assert(Member (instance  ?rifvar ) (class  <http://white.gobo/modelA#missing-use-of-var> ))) (<http://white.gobo/set-graph-in-errorstate> (<http://www.w3.org/2007/rif-builtin-function#concat> "Missing%20use%20for%20variable%20with%20name%20"   ?varname   "%28modelA%3Amissing-use-of-var%29"  ) ))

(defrule rule222
(TripleTemplate (subject  ?rifequal ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?rifleft ))
(TripleTemplate (subject  ?rifequal ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?rifright ))
(Member (class  <http://white.gobo/modelA#TestPatternEqualGenerator> ) (instance  ?rifequal ))
	=>
(assert(Member (instance  ?rifleft ) (class  <http://white.gobo/modelA#ExpressionGenerator> )))(assert(Member (instance  ?rifright ) (class  <http://white.gobo/modelA#ExpressionGenerator> ))))

(defrule rule223
(TripleTemplate (subject  ?rifright ) (predicate  <http://example.com/as-expression> ) (object  ?rightexpr ))
(TripleTemplate (subject  ?rifequal ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?rifleft ))
(TripleTemplate (subject  ?rifequal ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?rifright ))
(TripleTemplate (subject  ?rifleft ) (predicate  <http://example.com/as-constraint> ) (object  ?assignvar ))
(Member (class  <http://white.gobo/modelA#TestPatternLeftAssignGenerator> ) (instance  ?rifequal ))
	=>
(assert(Member (instance  ?assignvar ) (class  <http://white.gobo/modelA#VarAsConstExpr> )))(assert(TripleTemplate (subject  ?assignvar ) (predicate  <http://clips.script/var-as-const-expr> ) (object  ?rightexpr ))))

(defrule rule224
(Member (class  <http://white.gobo/modelA#TestPatternRightAssignGenerator> ) (instance  ?rifequal ))
(TripleTemplate (subject  ?rifequal ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?rifleft ))
	=>
(assert(Member (instance  ?rifleft ) (class  <http://white.gobo/modelA#ExpressionGenerator> ))))

(defrule rule225
(TripleTemplate (subject  ?rifright ) (predicate  <http://example.com/as-expression> ) (object  ?assignvar ))
(TripleTemplate (subject  ?rifleft ) (predicate  <http://example.com/as-expression> ) (object  ?leftexpr ))
(TripleTemplate (subject  ?rifequal ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?rifright ))
(TripleTemplate (subject  ?rifequal ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?rifleft ))
(Member (class  <http://white.gobo/modelA#TestPatternRightAssignGenerator> ) (instance  ?rifequal ))
	=>
(assert(Member (instance  ?assignvar ) (class  <http://white.gobo/modelA#VarAsConstExpr> )))(assert(TripleTemplate (subject  ?assignvar ) (predicate  <http://clips.script/var-as-const-expr> ) (object  ?leftexpr ))))

(defrule rule226
(Member (class  <http://white.gobo/modelA#TestPatternEqualGenerator> ) (instance  ?rifequal ))
(TripleTemplate (subject  ?rifleft ) (predicate  <http://example.com/as-expression> ) (object  ?leftexpr ))
(TripleTemplate (subject  ?rifequal ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?rifleft ))
(TripleTemplate (subject  ?rifequal ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?rifright ))
(TripleTemplate (subject  ?rifright ) (predicate  <http://example.com/as-expression> ) (object  ?rightexpr ))
(not
(exists
(TripleTemplate (subject  ?rifequal ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?x ))
)
)
	=>
 (bind ?pattern   (<http://white.gobo/new-blanknode>) ) (bind ?action   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifequal ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?pattern )))(assert(Member (instance  ?pattern ) (class  <http://clips.script/TestCE> )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/function-call> ) (object  ?action )))(assert(TripleTemplate (subject  ?action ) (predicate  <http://clips.script/function-name> ) (object  "eq" )))(assert(TripleTemplate (subject  ?action ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?leftexpr   ?rightexpr  )))))

(defrule rule227
(Member (class  <http://www.w3.org/2007/rif#Execute> ) (instance  ?rifexecute ))
(TripleTemplate (subject  ?rifop ) (predicate  <http://example.com/as-expression> ) (object  ?functionsymbol ))
(TripleTemplate (subject  ?functionsymbol ) (predicate  <http://clips.script/symbol> ) (object  ?functionname ))
(TripleTemplate (subject  ?rifexecute ) (predicate  <http://www.w3.org/2007/rif#target> ) (object  ?target ))
(TripleTemplate (subject  ?target ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?rifop ))
(TripleTemplate (subject  ?target ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?rifarglist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?rifarglist  ))

	=>
 (bind ?function   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifexecute ) (predicate  <http://example.com/as-action> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?function  ))))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-name> ) (object  ?functionname )))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>))))(assert(TripleTemplate (subject  ?function ) (predicate  <http://white.gobo/local/b/ncfe8f320_n36#add-args-from> ) (object  ?rifarglist ))))

(defrule rule228 (declare (salience 15))
(TripleTemplate (subject  ?function ) (predicate  <http://white.gobo/local/b/ncfe8f320_n36#add-args-from> ) (object  ?rifarglist ))
(TripleTemplate (subject  ?firstarg ) (predicate  <http://example.com/as-expression> ) (object  ?clipsexpression ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?rifarglist  ))

(test (eq ?firstarg   (<http://www.w3.org/2007/rif-builtin-function#get> ?rifarglist   "0^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

	=>
 (bind ?functionargs   (do-for-fact (( ?fcct11 TripleTemplate)) (and (eq ?fcct11:subject   ?function  )  (eq ?fcct11:predicate   <http://clips.script/function-args>  ) ) (fact-slot-value ?fcct11   object  ) )  ) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?function  )  (eq ?fct1:predicate   <http://clips.script/function-args>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?functionargs   ?clipsexpression  )))) (do-for-all-facts (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?function  )  (eq ?fct1:predicate   <http://white.gobo/local/b/ncfe8f320_n36#add-args-from>  ) ) (retract ?fct1  ) ) (assert(TripleTemplate (subject  ?function ) (predicate  <http://white.gobo/local/b/ncfe8f320_n36#add-args-from> ) (object  (<http://www.w3.org/2007/rif-builtin-function#remove> ?rifarglist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )))))

