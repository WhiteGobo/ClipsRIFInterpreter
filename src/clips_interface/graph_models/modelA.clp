
(defrule rule0
(Member (class  <http://white.gobo/modelA#SubclassPatternGenerator> ) (instance  ?rifmember ))
(TripleTemplate (subject  ?rifmember ) (predicate  <http://www.w3.org/2007/rif#sub> ) (object  ?rifsub ))
(TripleTemplate (subject  ?rifmember ) (predicate  <http://www.w3.org/2007/rif#super> ) (object  ?rifsuper ))
(TripleTemplate (subject  ?rifsub ) (predicate  <http://example.com/as-constraint> ) (object  ?constraintsub ))
(TripleTemplate (subject  ?rifsuper ) (predicate  <http://example.com/as-constraint> ) (object  ?constraintsuper ))
(not
(exists
(TripleTemplate (subject  ?rifmember ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?x ))
)
)
	=>
 (bind ?slotsuper   (<http://white.gobo/new-blanknode>) ) (bind ?slotsub   (<http://white.gobo/new-blanknode>) ) (bind ?pattern   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifmember ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?pattern )))(assert(Member (instance  ?pattern ) (class  <http://clips.script/TemplatePatternCE> )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/deftemplate-name> ) (object  "Subclass" )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/slot> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?slotsuper   ?slotsub  ))))(assert(TripleTemplate (subject  ?slotsuper ) (predicate  <http://clips.script/slot-name> ) (object  "super" )))(assert(TripleTemplate (subject  ?slotsuper ) (predicate  <http://clips.script/constraint> ) (object  ?constraintsuper )))(assert(TripleTemplate (subject  ?slotsub ) (predicate  <http://clips.script/slot-name> ) (object  "sub" )))(assert(TripleTemplate (subject  ?slotsub ) (predicate  <http://clips.script/constraint> ) (object  ?constraintsub ))))

(defrule rule1 (declare (salience 5))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifterm ))
(Member (class  <http://white.gobo/local/b/nfc895320_n9762#check-expression-needs-var> ) (instance  ?rifterm ))
(TripleTemplate (subject  ?rifterm ) (predicate  <http://example.com/as-expression> ) (object  ?clipsvar ))
	=>
(assert(TripleTemplate (subject  ?rifterm ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#expression-needs-var> ) (object  ?clipsvar ))))

(defrule rule2 (declare (salience 5))
(Member (class  <http://www.w3.org/2007/rif#Or> ) (instance  ?rifor ))
(TripleTemplate (subject  ?rifor ) (predicate  <http://www.w3.org/2007/rif#formulas> ) (object  ?formulalist ))
(TripleTemplate (subject  = (<http://www.w3.org/2007/rif-builtin-function#get> ?formulalist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )) (predicate  <http://white.gobo/modelA#binds-var> ) (object  ?clipsconstraint ))
(not
(exists
(and
(Member (class  <http://white.gobo/local/b/nfc895320_n9762#rifformula> ) (instance  ?otherformula ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?formulalist   ?otherformula  ))

(not
(TripleTemplate (subject  ?otherformula ) (predicate  <http://white.gobo/modelA#binds-var> ) (object  ?clipsconstraint ))
)
)
)
)
	=>
(assert(TripleTemplate (subject  ?rifor ) (predicate  <http://white.gobo/modelA#binds-var> ) (object  ?clipsconstraint ))))

(defrule rule3 (declare (salience 5))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?rifexternal ))
(or
(TripleTemplate (subject  ?rifpattern ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?rifexternal ))
(TripleTemplate (subject  ?rifpattern ) (predicate  <http://www.w3.org/2007/rif#sub> ) (object  ?rifexternal ))
(TripleTemplate (subject  ?rifpattern ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?rifexternal ))
(TripleTemplate (subject  ?rifpattern ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?rifexternal ))
(TripleTemplate (subject  ?rifpattern ) (predicate  <http://www.w3.org/2007/rif#super> ) (object  ?rifexternal ))
(TripleTemplate (subject  ?rifpattern ) (predicate  <http://www.w3.org/2007/rif#class> ) (object  ?rifexternal ))
(TripleTemplate (subject  ?rifpattern ) (predicate  <http://www.w3.org/2007/rif#instance> ) (object  ?rifexternal ))
)
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#add-pattern-from> ) (object  ?rifpattern ))
	=>
(assert(Member (instance  ?rifexternal ) (class  <http://white.gobo/local/b/nfc895320_n9762#check-constraint-needs-var> ))))

(defrule rule4 (declare (salience 5))
(Member (class  <http://www.w3.org/2007/rif#Exists> ) (instance  ?formula ))
	=>
 (bind ?clipsexists   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>))))(assert(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?clipsexists )))(assert(Member (instance  ?clipsexists ) (class  <http://clips.script/ExistsCE> )))(assert(TripleTemplate (subject  ?clipsexists ) (predicate  <http://clips.script/conditional-element> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>)))))

(defrule rule5 (declare (salience 5))
(Member (class  <http://example.com/ConstraintGenerator> ) (instance  ?riflist ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://www.w3.org/2007/rif#items> ) (object  ?itemlist ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#constraint-binds-var> ) (object  ?clipsconstraint ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?itemlist   ?rifvar  ))

	=>
(assert(TripleTemplate (subject  ?rifvar ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#constraint-binds-var> ) (object  ?clipsconstraint ))))

(defrule rule6 (declare (salience -7))
(Member (class  <http://white.gobo/modelA#ConditionGenerator> ) (instance  ?rifexternal ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?rifexternal ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#add-pattern-from> ) (object  ?rifexternal ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  ?formulalist ))
(not
(exists
(and
(TripleTemplate (subject  ?rifexternal ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#expressions-needs-var> ) (object  ?x ))
(not
(TripleTemplate (subject  ?rifexternal ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?x ))
)
)
)
)
(not
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?rifexternal ))
)
	=>
(assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?rifexternal ))) (do-for-all-facts (( ?fct21 TripleTemplate)) (and (eq ?fct21:subject   ?formulacontainer  )  (eq ?fct21:predicate   <http://white.gobo/local/b/nfc895320_n9762#formulalist>  ) ) (retract ?fct21  ) ) (assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?formulalist   ?rifexternal  ))))(assert(Member (instance  ?rifexternal ) (class  <http://white.gobo/modelA#TestPatternExternalGenerator> )))(assert(Member (instance  ?rifexternal ) (class  <http://white.gobo/modelA#PatternGenerator> ))))

(defrule rule7 (declare (salience 5))
(Member (class  <http://white.gobo/modelA#PatternGenerator> ) (instance  ?rifformula ))
(or
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#sub> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#instance> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#class> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#super> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?rifvar ))
)
(TripleTemplate (subject  ?rifvar ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#constraint-binds-var> ) (object  ?clipsconstraint ))
(not
(TripleTemplate (subject  ?rifformula ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?clipsconstraint ))
)
	=>
(assert(TripleTemplate (subject  ?rifformula ) (predicate  <http://white.gobo/modelA#binds-var> ) (object  ?clipsconstraint ))))

(defrule rule8 (declare (salience 5))
(or
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#Equal> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#Member> ) (instance  ?rifformula ))
)
(TripleTemplate (subject  ?rifrule ) (predicate  <http://www.w3.org/2007/rif#formula> ) (object  ?rifformula ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?clipsconstraint ))
	=>
(assert(TripleTemplate (subject  ?rifformula ) (predicate  <http://white.gobo/modelA#bound-variable> ) (object  ?clipsconstraint ))))

(defrule rule9 (declare (salience 20))
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?otherrifand ))
(TripleTemplate (subject  ?otherrifand ) (predicate  <http://www.w3.org/2007/rif#formulas> ) (object  ?formulalist ))
(TripleTemplate (subject  ?rifand ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#add-pattern-from> ) (object  ?otherrifand ))
(Member (class  <http://white.gobo/modelA#ConditionGenerator> ) (instance  ?rifformula ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?formulalist   ?rifformula  ))

(or
(Member (class  <http://www.w3.org/2007/rif#Not> ) (instance  ?rifand ))
(Member (class  <http://www.w3.org/2007/rif#Implies> ) (instance  ?rifand ))
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?rifand ))
(Member (class  <http://www.w3.org/2007/rif#Forall> ) (instance  ?rifand ))
)
	=>
(assert(TripleTemplate (subject  ?otherrifand ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?rifformula )))(assert(TripleTemplate (subject  ?rifand ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?otherrifand )))(assert(TripleTemplate (subject  ?rifand ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#add-pattern-from> ) (object  ?rifformula ))))

(defrule rule10 (declare (salience 11))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?rifexternal ))
(Member (class  <http://white.gobo/modelA#ConditionGenerator> ) (instance  ?rifexternal ))
(TripleTemplate (subject  ?rifexternal ) (predicate  <http://example.com/inherits-data> ) (object  ?rifvar ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifvar ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-expression> ) (object  ?clipsvar ))
	=>
(assert(TripleTemplate (subject  ?rifexternal ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#expressions-needs-var> ) (object  ?clipsvar ))))

(defrule rule11 (declare (salience 5))
(or
(Member (class  <http://www.w3.org/2007/rif#Exists> ) (instance  ?rifnot ))
(Member (class  <http://www.w3.org/2007/rif#INeg> ) (instance  ?rifnot ))
)
(TripleTemplate (subject  ?rifnot ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?clipsvar ))
(TripleTemplate (subject  ?rifnot ) (predicate  <http://www.w3.org/2007/rif#formula> ) (object  ?rifformula ))
(not
(exists
(TripleTemplate (subject  ?rifnot ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?subpattern ))
)
)
	=>
(assert(TripleTemplate (subject  ?rifformula ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?clipsvar ))))

(defrule rule12 (declare (salience 5))
(Member (class  <http://white.gobo/modelA#TripleTemplateGenerator> ) (instance  ?rifframe ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifvar ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsvar ))
(or
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?rifvar ))
)
	=>
(assert(Member (instance  ?clipsvar ) (class  <http://example.com/Variable> ))))

(defrule rule13 (declare (salience 5))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifvar ))
(TripleTemplate (subject  ?rifterm ) (predicate  <http://example.com/inherits-data> ) (object  ?rifvar ))
(Member (class  <http://white.gobo/local/b/nfc895320_n9762#check-constraint-needs-var> ) (instance  ?rifterm ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-expression> ) (object  ?clipsvar ))
	=>
(assert(TripleTemplate (subject  ?rifterm ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#constraint-needs-var> ) (object  ?clipsvar ))))

(defrule rule14 (declare (salience 5))
(Member (class  <http://white.gobo/modelA#ConstraintGenerator> ) (instance  ?riflist ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://www.w3.org/2007/rif#items> ) (object  ?itemlist ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#constraint-binds-var> ) (object  ?clipsconstraint ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?itemlist   ?rifvar  ))

	=>
(assert(TripleTemplate (subject  ?riflist ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#constraint-binds-var> ) (object  ?clipsconstraint ))))

(defrule rule15 (declare (salience -7))
(Member (class  <http://white.gobo/modelA#ConditionGenerator> ) (instance  ?rifequal ))
(Member (class  <http://www.w3.org/2007/rif#Equal> ) (instance  ?rifequal ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#add-pattern-from> ) (object  ?rifequal ))
(TripleTemplate (subject  ?rifequal ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?rifright ))
(TripleTemplate (subject  ?rifequal ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?rifleft ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  ?formulalist ))
(not
(exists
(and
(TripleTemplate (subject  ?rifright ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#expression-needs-var> ) (object  ?x ))
(not
(TripleTemplate (subject  ?rifequal ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?x ))
)
)
)
)
(not
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?rifequal ))
)
(not
(exists
(and
(TripleTemplate (subject  ?rifleft ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#expression-needs-var> ) (object  ?x ))
(not
(TripleTemplate (subject  ?rifequal ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?x ))
)
)
)
)
	=>
(assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?rifequal ))) (do-for-all-facts (( ?fct18 TripleTemplate)) (and (eq ?fct18:subject   ?formulacontainer  )  (eq ?fct18:predicate   <http://white.gobo/local/b/nfc895320_n9762#formulalist>  ) ) (retract ?fct18  ) ) (assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?formulalist   ?rifequal  ))))(assert(Member (instance  ?rifequal ) (class  <http://white.gobo/modelA#TestPatternEqualGenerator> )))(assert(Member (instance  ?rifequal ) (class  <http://white.gobo/modelA#PatternGenerator> )))(assert(Member (instance  ?rifleft ) (class  <http://white.gobo/modelA#ExpressionGenerator> )))(assert(Member (instance  ?rifright ) (class  <http://white.gobo/modelA#ExpressionGenerator> ))))

(defrule rule16 (declare (salience 5))
(Member (class  <http://www.w3.org/2007/rif#Slot> ) (instance  ?slot ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#add-pattern-from> ) (object  ?rifframe ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

	=>
(assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#add-pattern-from> ) (object  ?slot ))))

(defrule rule17 (declare (salience 11))
(Member (class  <http://www.w3.org/2007/rif#INeg> ) (instance  ?rifineg ))
(TripleTemplate (subject  ?rifineg ) (predicate  <http://example.com/inherits-data> ) (object  ?rifvarconsumer ))
(TripleTemplate (subject  ?rifvarconsumer ) (predicate  <http://example.com/as-expression> ) (object  ?clipsvar ))
	=>
(assert(TripleTemplate (subject  ?rifineg ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#subpattern-needs-variable> ) (object  ?clipsvar ))))

(defrule rule18 (declare (salience 5))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifvar ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsvar ))
(Member (class  <http://white.gobo/modelA#SubclassPatternGenerator> ) (instance  ?rifsubclass ))
(or
(TripleTemplate (subject  ?rifsubclass ) (predicate  <http://www.w3.org/2007/rif#sub> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifsubclass ) (predicate  <http://www.w3.org/2007/rif#super> ) (object  ?rifvar ))
)
	=>
(assert(Member (instance  ?clipsvar ) (class  <http://example.com/Variable> ))))

(defrule rule19 (declare (salience -12))
(Member (class  <http://www.w3.org/2007/rif#Equal> ) (instance  ?rifequal ))
(TripleTemplate (subject  ?rifequal ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?rifleft ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifleft ))
(TripleTemplate (subject  ?rifequal ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?rifright ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#add-pattern-from> ) (object  ?rifequal ))
(TripleTemplate (subject  ?rifleft ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsassign ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/modelA#as-defrule> ) (object  ?defrule ))
(not
(exists
(and
(TripleTemplate (subject  ?rifright ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#expression-needs-var> ) (object  ?x ))
(not
(TripleTemplate (subject  ?rifequal ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?x ))
)
)
)
)
(not
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?rifequal ))
)
(not
(TripleTemplate (subject  ?rifequal ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?clipsassign ))
)
	=>
(assert(TripleTemplate (subject  ?rifequal ) (predicate  <http://white.gobo/modelA#binds-var> ) (object  ?clipsassign )))(assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?rifequal )))(assert(Member (instance  ?rifequal ) (class  <http://white.gobo/modelA#TestPatternLeftAssignGenerator> )))(assert(Member (instance  ?rifequal ) (class  <http://white.gobo/modelA#PatternGenerator> )))(assert(Member (instance  ?rifright ) (class  <http://white.gobo/modelA#ExpressionGenerator> )))(assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?clipsassign ))))

(defrule rule20 (declare (salience 5))
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#binds-var> ) (object  ?clipsvar ))
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#transfer-variable-binding> ) (object  ?formulacontainer ))
	=>
(assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?clipsvar ))))

(defrule rule21 (declare (salience 5))
(Member (class  <http://white.gobo/modelA#PatternGenerator> ) (instance  ?rifatom ))
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#constraint-binds-var> ) (object  ?clipsconstraint ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?arglist   ?rifvar  ))

(not
(TripleTemplate (subject  ?rifatom ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?clipsconstraint ))
)
	=>
(assert(TripleTemplate (subject  ?rifatom ) (predicate  <http://white.gobo/modelA#binds-var> ) (object  ?clipsconstraint ))))

(defrule rule22 (declare (salience 5))
(Member (class  <http://white.gobo/local/b/nfc895320_n9762#check-expression-needs-var> ) (instance  ?rifterm ))
(TripleTemplate (subject  ?rifterm ) (predicate  <http://example.com/inherits-data> ) (object  ?rifvar ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifvar ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-expression> ) (object  ?clipsvar ))
	=>
(assert(TripleTemplate (subject  ?rifterm ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#expression-needs-var> ) (object  ?clipsvar ))))

(defrule rule23 (declare (salience 5))
(or
(Member (class  <http://white.gobo/modelA#SubclassPatternGenerator> ) (instance  ?rifobj ))
(Member (class  <http://white.gobo/modelA#TripleTemplateGenerator> ) (instance  ?rifobj ))
(Member (class  <http://white.gobo/modelA#MemberPatternGenerator> ) (instance  ?rifobj ))
)
(or
(TripleTemplate (subject  ?rifobj ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifobj ) (predicate  <http://www.w3.org/2007/rif#class> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifobj ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifobj ) (predicate  <http://www.w3.org/2007/rif#sub> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifobj ) (predicate  <http://www.w3.org/2007/rif#super> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifobj ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifobj ) (predicate  <http://www.w3.org/2007/rif#instance> ) (object  ?rifvar ))
)
(TripleTemplate (subject  ?rifvar ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#constraint-binds-var> ) (object  ?clipsconstraint ))
(not
(TripleTemplate (subject  ?rifobj ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?clipsconstraint ))
)
	=>
(assert(TripleTemplate (subject  ?rifobj ) (predicate  <http://white.gobo/modelA#binds-var> ) (object  ?clipsconstraint ))))

(defrule rule24 (declare (salience -1))
(or
(Member (class  <http://clips.script/Defrule> ) (instance  ?superpattern ))
(Member (class  <http://clips.script/NotCE> ) (instance  ?superpattern ))
(Member (class  <http://clips.script/OrCE> ) (instance  ?superpattern ))
(Member (class  <http://clips.script/ExistsCE> ) (instance  ?superpattern ))
(Member (class  <http://clips.script/AndCE> ) (instance  ?superpattern ))
)
(TripleTemplate (subject  ?superpattern ) (predicate  <http://clips.script/conditional-element> ) (object  ?patternlist ))
(or
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/modelA#as-defrule> ) (object  ?superpattern ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?superpattern ))
)
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  ?formulalist ))
(TripleTemplate (subject  = (<http://www.w3.org/2007/rif-builtin-function#get> ?formulalist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?subpattern ))
(exists
(TripleTemplate (subject  = (<http://www.w3.org/2007/rif-builtin-function#get> ?formulalist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )) (predicate  <http://white.gobo/modelA#lhs-pattern-after-conditions> ) (object  ?x ))
)
	=>
 (bind ?andpattern   (<http://white.gobo/new-blanknode>) )(assert(Member (instance  ?andpattern ) (class  <http://clips.script/AndCE> )))(assert(TripleTemplate (subject  ?andpattern ) (predicate  <http://clips.script/conditional-element> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?subpattern  ))))(assert(TripleTemplate (subject  (<http://www.w3.org/2007/rif-builtin-function#get> ?formulalist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )) (predicate  <http://white.gobo/local/b/nfc895320_n9762#transfer-after-conditions> ) (object  ?andpattern ))) (do-for-all-facts (( ?fct19 TripleTemplate)) (and (eq ?fct19:subject   ?formulacontainer  )  (eq ?fct19:predicate   <http://white.gobo/local/b/nfc895320_n9762#formulalist>  ) ) (retract ?fct19  ) ) (assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#remove> ?formulalist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )))) (do-for-all-facts (( ?fct20 TripleTemplate)) (and (eq ?fct20:subject   ?superpattern  )  (eq ?fct20:predicate   <http://clips.script/conditional-element>  ) ) (retract ?fct20  ) ) (assert(TripleTemplate (subject  ?superpattern ) (predicate  <http://clips.script/conditional-element> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?patternlist   ?andpattern  ))))(assert(TripleTemplate (subject  (<http://www.w3.org/2007/rif-builtin-function#get> ?formulalist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )) (predicate  <http://white.gobo/local/b/nfc895320_n9762#transfer-variable-binding> ) (object  ?formulacontainer ))))

(defrule rule25 (declare (salience 5))
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?rifand ))
(not
(exists
(and
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?superand ))
(TripleTemplate (subject  ?superand ) (predicate  <http://www.w3.org/2007/rif#formulas> ) (object  ?formulalist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?formulalist   ?rifand  ))

)
)
)
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
	=>
 (bind ?clipsand   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifand ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>))))(assert(TripleTemplate (subject  ?rifand ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?clipsand )))(assert(Member (instance  ?clipsand ) (class  <http://clips.script/AndCE> )))(assert(TripleTemplate (subject  ?clipsand ) (predicate  <http://clips.script/conditional-element> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>)))))

(defrule rule26 (declare (salience 5))
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?rifrule ))
(TripleTemplate (subject  ?rifrule ) (predicate  <http://www.w3.org/2007/rif#formulas> ) (object  ?formulalist ))
(or
(Member (class  <http://www.w3.org/2007/rif#Equal> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#Member> ) (instance  ?rifformula ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?formulalist   ?rifformula  ))

(TripleTemplate (subject  ?rifformula ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?clipsconstraint ))
	=>
(assert(TripleTemplate (subject  ?rifformula ) (predicate  <http://white.gobo/modelA#bound-variable> ) (object  ?clipsconstraint ))))

(defrule rule27 (declare (salience 5))
(or
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#content> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#class> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#super> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#instance> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#sub> ) (object  ?rifvar ))
)
(TripleTemplate (subject  ?rifvar ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#constraint-needs-var> ) (object  ?clipsvar ))
	=>
(assert(TripleTemplate (subject  ?rifformula ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#constraints-needs-variable> ) (object  ?clipsvar ))))

(defrule rule28 (declare (salience 5))
(Member (class  <http://white.gobo/modelA#ListAsConstraint> ) (instance  ?riflist ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#expression-needs-var> ) (object  ?unboundvar ))
(not
(TripleTemplate (subject  ?riflist ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?unboundvar ))
)
	=>
(assert(TripleTemplate (subject  ?riflist ) (predicate  <http://white.gobo/modelA#binds-var> ) (object  ?unboundvar ))))

(defrule rule29 (declare (salience 5))
(Member (class  <http://www.w3.org/2007/rif#Or> ) (instance  ?formula ))
	=>
 (bind ?clipsor   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>))))(assert(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?clipsor )))(assert(Member (instance  ?clipsor ) (class  <http://clips.script/OrCE> )))(assert(TripleTemplate (subject  ?clipsor ) (predicate  <http://clips.script/conditional-element> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>)))))

(defrule rule30 (declare (salience -13))
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?rifatom ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#add-pattern-from> ) (object  ?rifatom ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  ?formulalist ))
(not
(exists
(and
(TripleTemplate (subject  ?rifatom ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#constraints-needs-variable> ) (object  ?x ))
(not
(TripleTemplate (subject  ?rifatom ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?x ))
)
)
)
)
(not
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?rifatom ))
)
	=>
(assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?rifatom ))) (do-for-all-facts (( ?fct16 TripleTemplate)) (and (eq ?fct16:subject   ?formulacontainer  )  (eq ?fct16:predicate   <http://white.gobo/local/b/nfc895320_n9762#formulalist>  ) ) (retract ?fct16  ) ) (assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?formulalist   ?rifatom  ))))(assert(Member (instance  ?rifatom ) (class  <http://white.gobo/modelA#AtomPatternGenerator> )))(assert(Member (instance  ?rifatom ) (class  <http://white.gobo/modelA#PatternGenerator> ))))

(defrule rule31 (declare (salience -10))
(Member (class  <http://white.gobo/modelA#ConstraintGenerator> ) (instance  ?riflist ))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?riflist ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#expression-needs-var> ) (object  ?unboundvar ))
(not
(Member (class  <http://white.gobo/modelA#ExpressionGenerator> ) (instance  ?riflist ))
)
(not
(TripleTemplate (subject  ?riflist ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?unboundvar ))
)
	=>
(assert(Member (instance  ?riflist ) (class  <http://white.gobo/modelA#ListAsConstraint> ))))

(defrule rule32 (declare (salience 11))
(Member (class  <http://white.gobo/modelA#PatternGenerator> ) (instance  ?pattern ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?pattern ))
(TripleTemplate (subject  ?pattern ) (predicate  <http://example.com/inherits-data> ) (object  ?term ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?term ))
(TripleTemplate (subject  ?term ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsvar ))
(Atom (op  <http://white.gobo/local/b/nfc895320_n9762#always-false> ) (args ))
	=>
(assert(TripleTemplate (subject  ?term ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#expression-needs-var> ) (object  ?clipsvar ))))

(defrule rule33 (declare (salience 5))
(or
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#Equal> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#INeg> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#Or> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#Member> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#Exists> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#SubClass> ) (instance  ?formula ))
)
	=>
(assert(Member (instance  ?formula ) (class  <http://white.gobo/local/b/nfc895320_n9762#rifformula> ))))

(defrule rule34 (declare (salience 5))
(Member (class  <http://www.w3.org/2007/rif#INeg> ) (instance  ?formula ))
	=>
 (bind ?clipsnot   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>))))(assert(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?clipsnot )))(assert(Member (instance  ?clipsnot ) (class  <http://clips.script/NotCE> )))(assert(TripleTemplate (subject  ?clipsnot ) (predicate  <http://clips.script/conditional-element> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>)))))

(defrule rule35 (declare (salience 5))
(Member (class  <http://white.gobo/modelA#ConditionGenerator> ) (instance  ?rifequal ))
(TripleTemplate (subject  ?rifequal ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?right ))
(TripleTemplate (subject  ?rifequal ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?left ))
	=>
(assert(Member (instance  ?left ) (class  <http://white.gobo/local/b/nfc895320_n9762#check-expression-needs-var> )))(assert(Member (instance  ?right ) (class  <http://white.gobo/local/b/nfc895320_n9762#check-expression-needs-var> ))))

(defrule rule36 (declare (salience -9))
(Member (class  <http://www.w3.org/2007/rif#Member> ) (instance  ?rifmember ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#add-pattern-from> ) (object  ?rifmember ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  ?formulalist ))
(not
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?rifmember ))
)
(not
(exists
(and
(TripleTemplate (subject  ?rifmember ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#constraints-needs-variable> ) (object  ?x ))
(not
(TripleTemplate (subject  ?rifmember ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?x ))
)
)
)
)
	=>
(assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?rifmember ))) (do-for-all-facts (( ?fct22 TripleTemplate)) (and (eq ?fct22:subject   ?formulacontainer  )  (eq ?fct22:predicate   <http://white.gobo/local/b/nfc895320_n9762#formulalist>  ) ) (retract ?fct22  ) ) (assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?formulalist   ?rifmember  ))))(assert(Member (instance  ?rifmember ) (class  <http://white.gobo/modelA#MemberPatternGenerator> )))(assert(Member (instance  ?rifmember ) (class  <http://white.gobo/modelA#PatternGenerator> ))))

(defrule rule37 (declare (salience 5))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?rifexternal ))
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?arglist   ?rifexternal  ))

(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#add-pattern-from> ) (object  ?rifatom ))
	=>
(assert(Member (instance  ?rifexternal ) (class  <http://white.gobo/local/b/nfc895320_n9762#check-constraint-needs-var> ))))

(defrule rule38 (declare (salience 20))
(or
(Member (class  <http://www.w3.org/2007/rif#Forall> ) (instance  ?rifforall ))
(Member (class  <http://www.w3.org/2007/rif#Implies> ) (instance  ?rifforall ))
)
(TripleTemplate (subject  ?rifforall ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#add-pattern-from> ) (object  ?rifrule ))
(or
(TripleTemplate (subject  ?rifrule ) (predicate  <http://www.w3.org/2007/rif#formula> ) (object  ?rifformula ))
(TripleTemplate (subject  ?rifrule ) (predicate  <http://www.w3.org/2007/rif#if> ) (object  ?rifformula ))
)
(or
(Member (class  <http://www.w3.org/2007/rif#Forall> ) (instance  ?rifrule ))
(Member (class  <http://www.w3.org/2007/rif#Implies> ) (instance  ?rifrule ))
)
	=>
(assert(TripleTemplate (subject  ?rifrule ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?rifformula )))(assert(TripleTemplate (subject  ?rifforall ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?rifrule )))(assert(TripleTemplate (subject  ?rifforall ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#add-pattern-from> ) (object  ?rifformula ))))

(defrule rule39 (declare (salience 5))
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?rifand ))
(TripleTemplate (subject  ?rifand ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?subformula ))
(TripleTemplate (subject  ?rifand ) (predicate  <http://www.w3.org/2007/rif#formulas> ) (object  ?formulalist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?formulalist   ?subformula  ))

(TripleTemplate (subject  ?subformula ) (predicate  <http://white.gobo/modelA#binds-var> ) (object  ?clipsconstraint ))
	=>
(assert(TripleTemplate (subject  ?rifand ) (predicate  <http://white.gobo/modelA#binds-var> ) (object  ?clipsconstraint ))))

(defrule rule40 (declare (salience 11))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifvar ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-expression> ) (object  ?clipsvar ))
(TripleTemplate (subject  ?formula ) (predicate  <http://example.com/inherits-data> ) (object  ?rifvar ))
(Member (class  <http://www.w3.org/2007/rif#Exists> ) (instance  ?formula ))
(TripleTemplate (subject  ?formula ) (predicate  <http://www.w3.org/2007/rif#vars> ) (object  ?varlist ))
	=>
(assert(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#subpattern-needs-variable> ) (object  ?clipsvar ))))

(defrule rule41 (declare (salience 5))
(Member (class  <http://white.gobo/modelA#AtomPatternGenerator> ) (instance  ?rifobj ))
(TripleTemplate (subject  ?rifobj ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#constraint-binds-var> ) (object  ?clipsconstraint ))
(not
(TripleTemplate (subject  ?rifobj ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?clipsconstraint ))
)
	=>
(assert(TripleTemplate (subject  ?rifobj ) (predicate  <http://white.gobo/modelA#binds-var> ) (object  ?clipsconstraint ))))

(defrule rule42 (declare (salience 5))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifvar ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#use-expression-from> ) (object  ?rifexpression ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-expression> ) (object  ?clipsvar ))
(TripleTemplate (subject  ?rifexpression ) (predicate  <http://example.com/as-expression> ) (object  ?clipsexpression ))
	=>
(assert(TripleTemplate (subject  ?clipsvar ) (predicate  <http://clips.script/var-as-const-expr> ) (object  ?clipsexpression ))))

(defrule rule43 (declare (salience -12))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifright ))
(TripleTemplate (subject  ?rifright ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsassign ))
(TripleTemplate (subject  ?rifequal ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?rifright ))
(Member (class  <http://www.w3.org/2007/rif#Equal> ) (instance  ?rifequal ))
(TripleTemplate (subject  ?rifequal ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?rifleft ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#add-pattern-from> ) (object  ?rifequal ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/modelA#as-defrule> ) (object  ?defrule ))
(not
(TripleTemplate (subject  ?rifequal ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?clipsassign ))
)
(not
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?rifequal ))
)
(not
(exists
(and
(TripleTemplate (subject  ?rifleft ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#expression-needs-var> ) (object  ?x ))
(not
(TripleTemplate (subject  ?rifequal ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?x ))
)
)
)
)
	=>
(assert(TripleTemplate (subject  ?rifequal ) (predicate  <http://white.gobo/modelA#binds-var> ) (object  ?clipsassign )))(assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?rifequal )))(assert(Member (instance  ?rifequal ) (class  <http://white.gobo/modelA#TestPatternRightAssignGenerator> )))(assert(Member (instance  ?rifequal ) (class  <http://white.gobo/modelA#PatternGenerator> )))(assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?clipsassign ))))

(defrule rule44 (declare (salience -10))
(or
(Member (class  <http://www.w3.org/2007/rif#Implies> ) (instance  ?subpattern ))
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?subpattern ))
(Member (class  <http://www.w3.org/2007/rif#Or> ) (instance  ?subpattern ))
)
(TripleTemplate (subject  ?superpattern ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#add-pattern-from> ) (object  ?subpattern ))
(TripleTemplate (subject  ?superpattern ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  ?formulalist ))
(not
(TripleTemplate (subject  ?superpattern ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?subpattern ))
)
(not
(exists
(and
(TripleTemplate (subject  ?subpattern ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#constraints-needs-variable> ) (object  ?x ))
(not
(TripleTemplate (subject  ?subpattern ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?x ))
)
)
)
)
(exists
(TripleTemplate (subject  ?subpattern ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  ?x ))
)
(not
(exists
(and
(TripleTemplate (subject  ?subpattern ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#add-pattern-from> ) (object  ?subsub ))
(not
(TripleTemplate (subject  ?subpattern ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?subsub ))
)
)
)
)
	=>
(assert(TripleTemplate (subject  ?superpattern ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?subpattern ))) (do-for-all-facts (( ?fct27 TripleTemplate)) (and (eq ?fct27:subject   ?superpattern  )  (eq ?fct27:predicate   <http://white.gobo/local/b/nfc895320_n9762#formulalist>  ) ) (retract ?fct27  ) ) (assert(TripleTemplate (subject  ?superpattern ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?formulalist   ?subpattern  )))))

(defrule rule45 (declare (salience -7))
(Member (class  <http://www.w3.org/2007/rif#Member> ) (instance  ?rifmember ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#add-pattern-from> ) (object  ?rifmember ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  ?formulalist ))
(exists
(and
(TripleTemplate (subject  ?rifmember ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?clipsvar ))
(TripleTemplate (subject  ?x ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsvar ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?x ))
(or
(TripleTemplate (subject  ?rifmember ) (predicate  <http://www.w3.org/2007/rif#class> ) (object  ?x ))
(TripleTemplate (subject  ?rifmember ) (predicate  <http://www.w3.org/2007/rif#instance> ) (object  ?x ))
)
)
)
(not
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?rifmember ))
)
(not
(exists
(and
(TripleTemplate (subject  ?rifmember ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#constraints-needs-variable> ) (object  ?x ))
(not
(TripleTemplate (subject  ?rifmember ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?x ))
)
)
)
)
	=>
(assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?rifmember ))) (do-for-all-facts (( ?fct25 TripleTemplate)) (and (eq ?fct25:subject   ?formulacontainer  )  (eq ?fct25:predicate   <http://white.gobo/local/b/nfc895320_n9762#formulalist>  ) ) (retract ?fct25  ) ) (assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?formulalist   ?rifmember  ))))(assert(Member (instance  ?rifmember ) (class  <http://white.gobo/modelA#MemberPatternGenerator> )))(assert(Member (instance  ?rifmember ) (class  <http://white.gobo/modelA#PatternGenerator> ))))

(defrule rule46 (declare (salience -1))
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#lhs-pattern-after-conditions> ) (object  ?aftercondition ))
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#transfer-after-conditions> ) (object  ?andpattern ))
(TripleTemplate (subject  ?andpattern ) (predicate  <http://clips.script/conditional-element> ) (object  ?conditions ))
(not
(TripleTemplate (subject  ?aftercondition ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#transferred-after-condition> ) (object  ?andpattern ))
)
	=>
(assert(TripleTemplate (subject  ?aftercondition ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#transferred-after-condition> ) (object  ?andpattern ))) (do-for-all-facts (( ?fct24 TripleTemplate)) (and (eq ?fct24:subject   ?andpattern  )  (eq ?fct24:predicate   <http://clips.script/conditional-element>  ) ) (retract ?fct24  ) ) (assert(TripleTemplate (subject  ?andpattern ) (predicate  <http://clips.script/conditional-element> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?conditions   ?aftercondition  )))))

(defrule rule47 (declare (salience 5))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifvar ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsconstraint ))
	=>
(assert(TripleTemplate (subject  ?rifvar ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#constraint-binds-var> ) (object  ?clipsconstraint ))))

(defrule rule48 (declare (salience -8))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?rifframe ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#add-pattern-from> ) (object  ?rifframe ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?frameobject ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?slotlist  ))

(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  ?formulalist ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#add-pattern-from> ) (object  ?slot ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

(Member (class  <http://www.w3.org/2007/rif#Slot> ) (instance  ?slot ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?slotkey ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?slotvalue ))
(exists
(and
(TripleTemplate (subject  ?slot ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?x ))
(or
(TripleTemplate (subject  ?rifframe ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#triple-connected-to> ) (object  ?x ))
(TripleTemplate (subject  ?slot ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#triple-connected-to> ) (object  ?x ))
)
)
)
(not
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?slot ))
)
(not
(exists
(and
(TripleTemplate (subject  ?frameobject ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#constraint-needs-variable> ) (object  ?x ))
(not
(TripleTemplate (subject  ?slot ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?x ))
)
)
)
)
(not
(exists
(and
(TripleTemplate (subject  ?slot ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#constraints-needs-variable> ) (object  ?x ))
(not
(TripleTemplate (subject  ?slot ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?x ))
)
)
)
)
	=>
(assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?slot )))(assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?rifframe ))) (do-for-all-facts (( ?fct15 TripleTemplate)) (and (eq ?fct15:subject   ?formulacontainer  )  (eq ?fct15:predicate   <http://white.gobo/local/b/nfc895320_n9762#formulalist>  ) ) (retract ?fct15  ) ) (assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?formulalist   ?slot  ))))(assert(Member (instance  ?slot ) (class  <http://white.gobo/modelA#TripleTemplateGenerator> )))(assert(TripleTemplate (subject  ?slot ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#transfer-variable-binding> ) (object  ?formulacontainer )))(assert(Member (instance  ?rifframe ) (class  <http://white.gobo/modelA#TripleTemplateGenerator> )))(assert(TripleTemplate (subject  ?rifframe ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#transfer-variable-binding> ) (object  ?formulacontainer ))))

(defrule rule49 (declare (salience -13))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?rifframe ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?frameobject ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?slotlist  ))

(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#add-pattern-from> ) (object  ?rifframe ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#add-pattern-from> ) (object  ?slot ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

(Member (class  <http://www.w3.org/2007/rif#Slot> ) (instance  ?slot ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  ?formulalist ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?slotvalue ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?slotkey ))
(not
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?slot ))
)
(not
(exists
(and
(TripleTemplate (subject  ?slot ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#constraints-needs-variable> ) (object  ?x ))
(not
(TripleTemplate (subject  ?slot ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?x ))
)
)
)
)
(not
(exists
(and
(TripleTemplate (subject  ?frameobject ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#constraint-needs-variable> ) (object  ?x ))
(not
(TripleTemplate (subject  ?slot ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?x ))
)
)
)
)
	=>
(assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?slot )))(assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?rifframe ))) (do-for-all-facts (( ?fct12 TripleTemplate)) (and (eq ?fct12:subject   ?formulacontainer  )  (eq ?fct12:predicate   <http://white.gobo/local/b/nfc895320_n9762#formulalist>  ) ) (retract ?fct12  ) ) (assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?formulalist   ?slot  ))))(assert(Member (instance  ?slot ) (class  <http://white.gobo/modelA#TripleTemplateGenerator> )))(assert(TripleTemplate (subject  ?slot ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#transfer-variable-binding> ) (object  ?formulacontainer )))(assert(Member (instance  ?rifframe ) (class  <http://white.gobo/modelA#TripleTemplateGenerator> )))(assert(TripleTemplate (subject  ?rifframe ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#transfer-variable-binding> ) (object  ?formulacontainer ))))

(defrule rule50 (declare (salience -100))
(TripleTemplate (subject  ?rif ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#add-pattern-from> ) (object  ?pattern ))
(not
(TripleTemplate (subject  ?rif ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?pattern ))
)
	=>
(assert(Member (instance  ?pattern ) (class  <http://example.com/misses-bound-variables> )))(assert(TripleTemplate (subject  ?rif ) (predicate  <http://example.com/misses-pattern-for> ) (object  ?pattern ))) (<http://white.gobo/set-graph-in-errorstate> "Dont%20know%20where%20to%20add%20pattern%20for%20a%20formula%28ex%3Amisses-bound-variables%29"  ))

(defrule rule51 (declare (salience -1))
(Member (class  <http://white.gobo/modelA#MultiPatternGenerator> ) (instance  ?formula ))
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#as-multi-lhs-pattern> ) (object  ?subpattern ))
(or
(Member (class  <http://clips.script/OrCE> ) (instance  ?superpattern ))
(Member (class  <http://clips.script/NotCE> ) (instance  ?superpattern ))
(Member (class  <http://clips.script/AndCE> ) (instance  ?superpattern ))
(Member (class  <http://clips.script/ExistsCE> ) (instance  ?superpattern ))
(Member (class  <http://clips.script/Defrule> ) (instance  ?superpattern ))
)
(TripleTemplate (subject  ?superpattern ) (predicate  <http://clips.script/conditional-element> ) (object  ?patternlist ))
(or
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?superpattern ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/modelA#as-defrule> ) (object  ?superpattern ))
)
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  ?formulalist ))
(test (eq ?formula   (<http://www.w3.org/2007/rif-builtin-function#get> ?formulalist   "0^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

	=>
 (do-for-all-facts (( ?fct26 TripleTemplate)) (and (eq ?fct26:subject   ?formulacontainer  )  (eq ?fct26:predicate   <http://white.gobo/local/b/nfc895320_n9762#formulalist>  ) ) (retract ?fct26  ) ) (assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#remove> ?formulalist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )))) (do-for-all-facts (( ?fct17 TripleTemplate)) (and (eq ?fct17:subject   ?superpattern  )  (eq ?fct17:predicate   <http://clips.script/conditional-element>  ) ) (retract ?fct17  ) ) (assert(TripleTemplate (subject  ?superpattern ) (predicate  <http://clips.script/conditional-element> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?patternlist   ?subpattern  ))))(assert(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#transfer-variable-binding> ) (object  ?formulacontainer ))))

(defrule rule52 (declare (salience 5))
(Member (class  <http://white.gobo/modelA#AtomPatternGenerator> ) (instance  ?rifatom ))
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifvar ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?arglist   ?rifvar  ))

(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsvar ))
	=>
(assert(Member (instance  ?clipsvar ) (class  <http://example.com/Variable> ))))

(defrule rule53 (declare (salience -13))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?rifexternal ))
(TripleTemplate (subject  ?rifexternal ) (predicate  <http://www.w3.org/2007/rif#content> ) (object  ?rifatom ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#add-pattern-from> ) (object  ?rifexternal ))
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?rifconstiristring ))
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?arglist  ))

(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/modelA#as-defrule> ) (object  ?defrule ))
(TripleTemplate (subject  ?rifconstiristring ) (predicate  <http://www.w3.org/2007/rif#constIRI> ) (object  "http%3A%2F%2Fwww.w3.org%2F2007%2Frif-builtin-predicate%23iri-string^^http://www.w3.org/2001/XMLSchema#anyURI" ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?targetiri ))
(test (eq ?targetiri   (<http://www.w3.org/2007/rif-builtin-function#get> ?arglist   "0^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

(TripleTemplate (subject  = (<http://www.w3.org/2007/rif-builtin-function#get> ?arglist   "1^^http://www.w3.org/2001/XMLSchema#integer"  )) (predicate  <http://example.com/as-expression> ) (object  ?clipsassign ))
(not
(TripleTemplate (subject  ?rifexternal ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?clipsassign ))
)
(not
(exists
(and
(TripleTemplate (subject  = (<http://www.w3.org/2007/rif-builtin-function#get> ?arglist   "1^^http://www.w3.org/2001/XMLSchema#integer"  )) (predicate  <http://white.gobo/local/b/nfc895320_n9762#expression-needs-var> ) (object  ?x ))
(not
(TripleTemplate (subject  ?rifexternal ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?x ))
)
)
)
)
(not
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?rifexternal ))
)
	=>
(assert(Member (instance  ?rifexternal ) (class  <http://white.gobo/modelA#AssignGenerator> )))(assert(TripleTemplate (subject  ?targetiri ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#use-expression-from> ) (object  (<http://www.w3.org/2007/rif-builtin-function#get> ?arglist   "1^^http://www.w3.org/2001/XMLSchema#integer"  ))))(assert(Member (instance  (<http://www.w3.org/2007/rif-builtin-function#get> ?arglist   "1^^http://www.w3.org/2001/XMLSchema#integer"  )) (class  <http://white.gobo/modelA#ExpressionGenerator> )))(assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?rifexternal )))(assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  (<http://www.w3.org/2007/rif-builtin-function#get> ?arglist   "1^^http://www.w3.org/2001/XMLSchema#integer"  )))))

(defrule rule54 (declare (salience 5))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifvar ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsvar ))
(Member (class  <http://white.gobo/modelA#MemberPatternGenerator> ) (instance  ?rifmember ))
(or
(TripleTemplate (subject  ?rifmember ) (predicate  <http://www.w3.org/2007/rif#instance> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifmember ) (predicate  <http://www.w3.org/2007/rif#class> ) (object  ?rifvar ))
)
	=>
(assert(Member (instance  ?clipsvar ) (class  <http://example.com/Variable> ))))

(defrule rule55 (declare (salience -13))
(Member (class  <http://www.w3.org/2007/rif#Subclass> ) (instance  ?rifmember ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#add-pattern-from> ) (object  ?rifmember ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  ?formulalist ))
(not
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?rifmember ))
)
(not
(exists
(and
(TripleTemplate (subject  ?rifmember ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#constraints-needs-variable> ) (object  ?x ))
(not
(TripleTemplate (subject  ?rifmember ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?x ))
)
)
)
)
	=>
(assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?rifmember ))) (do-for-all-facts (( ?fct11 TripleTemplate)) (and (eq ?fct11:subject   ?formulacontainer  )  (eq ?fct11:predicate   <http://white.gobo/local/b/nfc895320_n9762#formulalist>  ) ) (retract ?fct11  ) ) (assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?formulalist   ?rifmember  ))))(assert(Member (instance  ?rifmember ) (class  <http://white.gobo/modelA#SubclassPatternGenerator> )))(assert(Member (instance  ?rifmember ) (class  <http://white.gobo/modelA#PatternGenerator> ))))

(defrule rule56 (declare (salience 5))
(or
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?superformula ))
(Member (class  <http://www.w3.org/2007/rif#Or> ) (instance  ?superformula ))
)
(TripleTemplate (subject  ?superformula ) (predicate  <http://white.gobo/modelA#binds-var> ) (object  ?clipsvar ))
(TripleTemplate (subject  ?superformula ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#add-pattern-from> ) (object  ?subformula ))
(not
(TripleTemplate (subject  ?superformula ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?subformula ))
)
	=>
(assert(TripleTemplate (subject  ?subformula ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?clipsvar ))))

(defrule rule57 (declare (salience 10))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifvar ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsvar ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#add-pattern-from> ) (object  ?rifframe ))
(not
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?rifframe ))
)
	=>
(assert(TripleTemplate (subject  ?rifframe ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#triple-connected-to> ) (object  ?clipsvar ))))

(defrule rule58 (declare (salience 5))
(or
(TripleTemplate (subject  ?rifobj ) (predicate  <http://www.w3.org/2007/rif#if> ) (object  ?formula ))
(TripleTemplate (subject  ?rifobj ) (predicate  <http://www.w3.org/2007/rif#pattern> ) (object  ?formula ))
(TripleTemplate (subject  ?rifobj ) (predicate  <http://www.w3.org/2007/rif#formula> ) (object  ?formula ))
)
(exists
(TripleTemplate (subject  ?rifobj ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  ?x ))
)
	=>
(assert(TripleTemplate (subject  ?rifobj ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#add-pattern-from> ) (object  ?formula ))))

(defrule rule59 (declare (salience -1))
(or
(Member (class  <http://clips.script/Defrule> ) (instance  ?superpattern ))
(Member (class  <http://clips.script/NotCE> ) (instance  ?superpattern ))
(Member (class  <http://clips.script/AndCE> ) (instance  ?superpattern ))
(Member (class  <http://clips.script/OrCE> ) (instance  ?superpattern ))
(Member (class  <http://clips.script/ExistsCE> ) (instance  ?superpattern ))
)
(TripleTemplate (subject  ?superpattern ) (predicate  <http://clips.script/conditional-element> ) (object  ?patternlist ))
(or
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?superpattern ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/modelA#as-defrule> ) (object  ?superpattern ))
)
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  ?formulalist ))
(TripleTemplate (subject  = (<http://www.w3.org/2007/rif-builtin-function#get> ?formulalist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?subpattern ))
(not
(Member (class  <http://white.gobo/modelA#MultiPatternGenerator> ) (instance  = (<http://www.w3.org/2007/rif-builtin-function#get> ?formulalist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )))
)
(not
(exists
(TripleTemplate (subject  = (<http://www.w3.org/2007/rif-builtin-function#get> ?formulalist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )) (predicate  <http://white.gobo/modelA#lhs-pattern-after-conditions> ) (object  ?aftercondition ))
)
)
	=>
 (do-for-all-facts (( ?fct13 TripleTemplate)) (and (eq ?fct13:subject   ?formulacontainer  )  (eq ?fct13:predicate   <http://white.gobo/local/b/nfc895320_n9762#formulalist>  ) ) (retract ?fct13  ) ) (assert(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#remove> ?formulalist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )))) (do-for-all-facts (( ?fct23 TripleTemplate)) (and (eq ?fct23:subject   ?superpattern  )  (eq ?fct23:predicate   <http://clips.script/conditional-element>  ) ) (retract ?fct23  ) ) (assert(TripleTemplate (subject  ?superpattern ) (predicate  <http://clips.script/conditional-element> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?patternlist   ?subpattern  ))))(assert(TripleTemplate (subject  (<http://www.w3.org/2007/rif-builtin-function#get> ?formulalist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )) (predicate  <http://white.gobo/local/b/nfc895320_n9762#transfer-variable-binding> ) (object  ?formulacontainer ))))

(defrule rule60 (declare (salience 5))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?rifexternal ))
(Member (class  <http://white.gobo/modelA#PatternGenerator> ) (instance  ?rifexternal ))
(TripleTemplate (subject  ?rifexternal ) (predicate  <http://www.w3.org/2007/rif#content> ) (object  ?rifatom ))
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
(or
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?arg ))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?arg ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?arglist   ?arg  ))

(TripleTemplate (subject  ?arg ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#expression-needs-var> ) (object  ?clipsvar ))
	=>
(assert(TripleTemplate (subject  ?rifexternal ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#constraints-needs-variable> ) (object  ?clipsvar ))))

(defrule rule61 (declare (salience 5))
(Member (class  <http://white.gobo/modelA#ConstraintGenerator> ) (instance  ?riflist ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://www.w3.org/2007/rif#rest> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#constraint-binds-var> ) (object  ?clipsconstraint ))
	=>
(assert(TripleTemplate (subject  ?riflist ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#constraint-binds-var> ) (object  ?clipsconstraint ))))

(defrule rule62 (declare (salience 5))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#constraint-needs-var> ) (object  ?clipsvar ))
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?arglist   ?rifvar  ))

	=>
(assert(TripleTemplate (subject  ?rifatom ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#constraints-needs-variable> ) (object  ?clipsvar ))))

(defrule rule63 (declare (salience -100))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  ?formulalist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#numeric-greater-than> (<http://www.w3.org/2007/rif-builtin-function#count> ?formulalist  )  "0^^http://www.w3.org/2001/XMLSchema#integer"  ))

	=>
(assert(Member (instance  (<http://www.w3.org/2007/rif-builtin-function#get> ?formulalist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )) (class  <http://example.com/couldnt-translate-to-pattern> )))(assert(Member (instance  ?formulacontainer ) (class  <http://example.com/missing-translated-pattern> ))) (<http://white.gobo/set-graph-in-errorstate> "Couldnt%20translate%20formula%20to%20pattern.%28ex%3Acouldnt-translate-to-pattern%20ex%3Amissing-translated-pattern%29"  ))

(defrule rule64 (declare (salience 5))
(or
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#Equal> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#INeg> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#Member> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#Exists> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#SubClass> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#Or> ) (instance  ?formula ))
)
(or
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?rifand ))
(Member (class  <http://www.w3.org/2007/rif#Or> ) (instance  ?rifand ))
)
(TripleTemplate (subject  ?rifand ) (predicate  <http://www.w3.org/2007/rif#formulas> ) (object  ?formulalist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?formulalist   ?formula  ))

(exists
(TripleTemplate (subject  ?rifand ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  ?x ))
)
	=>
(assert(TripleTemplate (subject  ?rifand ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#add-pattern-from> ) (object  ?formula ))))

(defrule rule65 (declare (salience 5))
(Member (class  <http://www.w3.org/2007/rif#Slot> ) (instance  ?slot ))
(Member (class  <http://white.gobo/modelA#PatternGenerator> ) (instance  ?rifframe ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

(or
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?rifvar ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?rifvar ))
)
(TripleTemplate (subject  ?rifvar ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#constraint-binds-var> ) (object  ?clipsconstraint ))
(not
(TripleTemplate (subject  ?rifframe ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?clipsconstraint ))
)
	=>
(assert(TripleTemplate (subject  ?rifframe ) (predicate  <http://white.gobo/modelA#binds-var> ) (object  ?clipsconstraint ))))

(defrule rule66 (declare (salience -10))
(or
(Member (class  <http://www.w3.org/2007/rif#Exists> ) (instance  ?subpattern ))
(Member (class  <http://www.w3.org/2007/rif#INeg> ) (instance  ?subpattern ))
)
(TripleTemplate (subject  ?superpattern ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#add-pattern-from> ) (object  ?subpattern ))
(TripleTemplate (subject  ?superpattern ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  ?formulalist ))
(not
(TripleTemplate (subject  ?superpattern ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?subpattern ))
)
(not
(exists
(and
(TripleTemplate (subject  ?subpattern ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#subpattern-needs-variable> ) (object  ?x ))
(not
(TripleTemplate (subject  ?superpattern ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?x ))
)
)
)
)
(not
(exists
(and
(TripleTemplate (subject  ?subpattern ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#add-pattern-from> ) (object  ?subsub ))
(not
(TripleTemplate (subject  ?subpattern ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?subsub ))
)
)
)
)
	=>
(assert(TripleTemplate (subject  ?superpattern ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?subpattern ))) (do-for-all-facts (( ?fct14 TripleTemplate)) (and (eq ?fct14:subject   ?superpattern  )  (eq ?fct14:predicate   <http://white.gobo/local/b/nfc895320_n9762#formulalist>  ) ) (retract ?fct14  ) ) (assert(TripleTemplate (subject  ?superpattern ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?formulalist   ?subpattern  )))))

(defrule rule67 (declare (salience 5))
(or
(Member (class  <http://www.w3.org/2007/rif#Implies> ) (instance  ?rifrule ))
(Member (class  <http://www.w3.org/2007/rif#Forall> ) (instance  ?rifrule ))
)
(TripleTemplate (subject  ?group ) (predicate  <http://www.w3.org/2007/rif#sentences> ) (object  ?sentences ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?sentences   ?rifrule  ))

(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?sentences  ))

	=>
 (bind ?defrule   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifrule ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#formulalist> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>))))(assert(TripleTemplate (subject  ?rifrule ) (predicate  <http://white.gobo/modelA#as-defrule> ) (object  ?defrule )))(assert(Member (instance  ?defrule ) (class  <http://clips.script/Defrule> )))(assert(TripleTemplate (subject  ?defrule ) (predicate  <http://clips.script/conditional-element> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>)))))

(defrule rule68 (declare (salience 5))
(or
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?targetiri ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?targetiri ))
)
(or
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?targetstring ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?targetstring ))
)
(TripleTemplate (subject  ?rifconstiristring ) (predicate  <http://www.w3.org/2007/rif#constIRI> ) (object  "http%3A%2F%2Fwww.w3.org%2F2007%2Frif-builtin-predicate%23iri-string^^http://www.w3.org/2001/XMLSchema#anyURI" ))
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?rifconstiristring ))
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
(test (eq ?targetiri   (<http://www.w3.org/2007/rif-builtin-function#get> ?arglist   "0^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

(test (eq ?targetstring   (<http://www.w3.org/2007/rif-builtin-function#get> ?arglist   "1^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

(TripleTemplate (subject  ?rifexternal ) (predicate  <http://www.w3.org/2007/rif#content> ) (object  ?rifatom ))
	=>
(assert(Member (instance  ?targetiri ) (class  <http://white.gobo/local/b/nfc895320_n9762#check-expression-needs-var> )))(assert(Member (instance  ?targetstring ) (class  <http://white.gobo/local/b/nfc895320_n9762#check-expression-needs-var> ))))

(defrule rule69 (declare (salience 5))
(or
(Member (class  <http://www.w3.org/2007/rif#Forall> ) (instance  ?formulacontainer ))
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?formulacontainer ))
(Member (class  <http://www.w3.org/2007/rif#Implies> ) (instance  ?formulacontainer ))
)
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#add-pattern-from> ) (object  ?formula ))
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?clipsvar ))
(not
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?formula ))
)
	=>
(assert(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?clipsvar ))))

(defrule rule70 (declare (salience -10))
(Member (class  <http://white.gobo/modelA#ConstraintGenerator> ) (instance  ?riflist ))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?riflist ))
(not
(Member (class  <http://white.gobo/modelA#ListAsConstraint> ) (instance  ?riflist ))
)
(not
(exists
(TripleTemplate (subject  ?riflist ) (predicate  <http://www.w3.org/2007/rif#rest> ) (object  ?rest ))
)
)
(not
(exists
(and
(TripleTemplate (subject  ?riflist ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#expression-needs-var> ) (object  ?x ))
(not
(TripleTemplate (subject  ?riflist ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#bound-variable> ) (object  ?x ))
)
)
)
)
	=>
(assert(Member (instance  ?riflist ) (class  <http://white.gobo/modelA#ExpressionGenerator> ))))

(defrule rule71 (declare (salience 5))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?arg ))
(TripleTemplate (subject  ?arg ) (predicate  <http://example.com/as-expression> ) (object  ?clipsvar ))
(Member (class  <http://white.gobo/modelA#PatternGenerator> ) (instance  ?rifexternal ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?rifexternal ))
(TripleTemplate (subject  ?rifexternal ) (predicate  <http://www.w3.org/2007/rif#content> ) (object  ?rifatom ))
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?arglist   ?arg  ))

	=>
(assert(TripleTemplate (subject  ?rifexternal ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#constraints-needs-variable> ) (object  ?clipsvar ))))

(defrule rule72 (declare (salience 10))
(Member (class  <http://www.w3.org/2007/rif#Slot> ) (instance  ?rifslot ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifvar ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsvar ))
(or
(TripleTemplate (subject  ?rifslot ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?rifvar ))
(TripleTemplate (subject  ?rifslot ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?rifvar ))
)
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#add-pattern-from> ) (object  ?rifframe ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?rifslot  ))

(not
(TripleTemplate (subject  ?formulacontainer ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#added-pattern-from> ) (object  ?rifframe ))
)
	=>
(assert(TripleTemplate (subject  ?rifslot ) (predicate  <http://white.gobo/local/b/nfc895320_n9762#triple-connected-to> ) (object  ?clipsvar ))))

(defrule rule73 (declare (salience -1))
(Atom (op  <http://example.com/currentfactindex> ) (args  ?factindex ))
(exists
(and
(TripleTemplate (subject  ?othervar ) (predicate  <http://clips.script/variable-name> ) (object  ?tmpname ))
(test (eq ?tmpname   (<http://www.w3.org/2007/rif-builtin-function#concat> "fct"   ?factindex  ) ))

)
)
	=>
 (retract(assert(Atom (op  <http://example.com/currentfactindex> ) (args  ?factindex ))) )(assert(Atom (op  <http://example.com/currentfactindex> ) (args  (<http://www.w3.org/2007/rif-builtin-function#numeric-add> ?factindex   "1^^http://www.w3.org/2001/XMLSchema#integer"  )))))

(defrule rule74 (declare (salience -102))
(Member (class  <http://clips.script/Variable> ) (instance  ?clipsvar ))
(not
(exists
(TripleTemplate (subject  ?clipsvar ) (predicate  <http://clips.script/var-as-const-expr> ) (object  ?varname ))
)
)
(not
(exists
(TripleTemplate (subject  ?clipsvar ) (predicate  <http://clips.script/variable-name> ) (object  ?varname ))
)
)
	=>
(assert(Member (instance  ?clipsvar ) (class  <http://white.gobo/modelA#missing-var-expression> ))) (<http://white.gobo/set-graph-in-errorstate> "A%20cs%3AVariable%20has%20no%20expression.%20missing%20cs%3Avariable-name%20or%20cs%3Avar-as-const-expr.%28modelA%3Amissing-var-expression%29"  ))

(defrule rule75 (declare (salience -1))
(Member (class  <http://clips.script/Variable> ) (instance  ?factvar ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://example.com/as-expression> ) (object  ?factvar ))
(or
(Member (class  <http://www.w3.org/2007/rif#Equal> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#Subclass> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#Member> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?rifformula ))
)
(Atom (op  <http://example.com/currentfactindex> ) (args  ?factindex ))
(not
(exists
(and
(TripleTemplate (subject  ?othervar ) (predicate  <http://clips.script/variable-name> ) (object  ?tmpname ))
(test (eq ?tmpname   (<http://www.w3.org/2007/rif-builtin-function#concat> "fct"   ?factindex  ) ))

)
)
)
(not
(exists
(TripleTemplate (subject  ?factvar ) (predicate  <http://clips.script/variable-name> ) (object  ?factname ))
)
)
	=>
 (retract(assert(Atom (op  <http://example.com/currentfactindex> ) (args  ?factindex ))) )(assert(Atom (op  <http://example.com/currentfactindex> ) (args  (<http://www.w3.org/2007/rif-builtin-function#numeric-add> ?factindex   "1^^http://www.w3.org/2001/XMLSchema#integer"  ))))(assert(Member (instance  ?factvar ) (class  <http://clips.script/Variable> )))(assert(TripleTemplate (subject  ?factvar ) (predicate  <http://clips.script/variable-name> ) (object  (<http://www.w3.org/2007/rif-builtin-function#concat> "fct"   ?factindex  )))))

(defrule rule76 (declare (salience 60))
(TripleTemplate (subject  ?rifnode ) (predicate  <http://www.w3.org/2007/rif#value> ) (object  ?value ))
	=>
 (bind ?clipsnode   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsnode )))(assert(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/as-expression> ) (object  ?clipsnode )))(assert(TripleTemplate (subject  ?clipsnode ) (predicate  <http://clips.script/string> ) (object  (<http://white.gobo/literal-to-clipsconstant> ?value  ))))(assert(TripleTemplate (subject  ?clipsnode ) (predicate  <http://example.com/as-constraint-needs-additional-conditionals> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>)))))

(defrule rule77
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifvar ))
(TripleTemplate (subject  ?rifforall ) (predicate  <http://www.w3.org/2007/rif#vars> ) (object  ?varlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?varlist   ?rifvar  ))

(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?varlist  ))

	=>
 (bind ?clipsnode   (<http://white.gobo/new-blanknode>) )(assert(Member (instance  ?clipsnode ) (class  <http://clips.script/Variable> )))(assert(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/provides-expression> ) (object  ?clipsnode )))(assert(TripleTemplate (subject  ?clipsnode ) (predicate  <http://example.com/as-constraint-needs-additional-conditionals> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>)))))

(defrule rule78 (declare (salience -100))
(TripleTemplate (subject  ?riflocal ) (predicate  <http://www.w3.org/2007/rif#constname> ) (object  ?name ))
(not
(exists
(and
(Member (class  <http://www.w3.org/2007/rif#Document> ) (instance  ?rifdocument ))
(TripleTemplate (subject  ?rifdocument ) (predicate  <http://example.com/inherits-data> ) (object  ?riflocal ))
)
)
)
	=>
(assert(Member (instance  ?riflocal ) (class  <http://white.gobo/modelA#missing-localterm> ))) (<http://white.gobo/set-graph-in-errorstate> "Missing%20connection%20of%20local%20constant%20to%20its%20document.%28modelA%3Amissing-localterm%29"  ))

(defrule rule79 (declare (salience -100))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://www.w3.org/2007/rif#varname> ) (object  ?varname ))
(not
(exists
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/provides-expression> ) (object  ?clipsnode ))
)
)
(not
(exists
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-expression> ) (object  ?clipsnode ))
)
)
	=>
(assert(Member (instance  ?rifvar ) (class  <http://white.gobo/modelA#missing-var-binding> ))) (<http://white.gobo/set-graph-in-errorstate> (<http://www.w3.org/2007/rif-builtin-function#concat> "Missing%20binding%20for%20rif%3AVar%20with%20name%20"   ?varname   "%20%28modelA%3Amissing-var-binding%29.%20Might%20be%20missing%20mention%20of%20variable%20in%20rif%3AForall%20or%20rif%3AExists."  ) ))

(defrule rule80 (declare (salience -102))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/provides-expression> ) (object  ?clipsvar ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://www.w3.org/2007/rif#varname> ) (object  ?varname ))
(not
(exists
(TripleTemplate (subject  ?rifvarchild ) (predicate  <http://example.com/as-expression> ) (object  ?clipsvar ))
)
)
	=>
(assert(Member (instance  ?rifvar ) (class  <http://white.gobo/modelA#missing-use-of-var> ))) (<http://white.gobo/set-graph-in-errorstate> (<http://www.w3.org/2007/rif-builtin-function#concat> "Missing%20use%20for%20variable%20with%20name%20"   ?varname   "%28modelA%3Amissing-use-of-var%29"  ) ))

(defrule rule81 (declare (salience -1))
(Member (class  <http://example.com/Variable> ) (instance  ?factvar ))
(Atom (op  <http://example.com/currentfactindex> ) (args  ?factindex ))
(not
(exists
(TripleTemplate (subject  ?factvar ) (predicate  <http://clips.script/variable-name> ) (object  ?factname ))
)
)
(not
(exists
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/provides-expression> ) (object  ?factvar ))
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

(defrule rule82
(TripleTemplate (subject  ?varchild ) (predicate  <http://www.w3.org/2007/rif#varname> ) (object  ?varname ))
(TripleTemplate (subject  ?varparent ) (predicate  <http://www.w3.org/2007/rif#varname> ) (object  ?varname ))
(TripleTemplate (subject  ?varparent ) (predicate  <http://example.com/inherits-data> ) (object  ?varchild ))
(TripleTemplate (subject  ?varparent ) (predicate  <http://example.com/provides-expression> ) (object  ?clipsvar ))
	=>
(assert(TripleTemplate (subject  ?varchild ) (predicate  <http://example.com/as-expression> ) (object  ?clipsvar )))(assert(TripleTemplate (subject  ?varchild ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsvar ))))

(defrule rule83
(TripleTemplate (subject  ?rifdo ) (predicate  <http://www.w3.org/2007/rif#actionVar> ) (object  ?actionvar ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?actionvar  ))

(TripleTemplate (subject  ?rifvar ) (predicate  <http://www.w3.org/2007/rif#varname> ) (object  ?varname ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?actionvar   ?rifvar  ))

	=>
 (bind ?clipsnode   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsnode )))(assert(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-expression> ) (object  ?clipsnode )))(assert(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/provides-expression> ) (object  ?clipsnode )))(assert(TripleTemplate (subject  ?clipsnode ) (predicate  <http://clips.script/variable-name> ) (object  ?varname )))(assert(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/inherits-data> ) (object  ?rifdo )))(assert(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/inherits-data> ) (object  (<http://www.w3.org/2007/rif-builtin-function#get> ?actionvar   "1^^http://www.w3.org/2001/XMLSchema#integer"  )))))

(defrule rule84 (declare (salience 60))
(TripleTemplate (subject  ?rifnode ) (predicate  <http://www.w3.org/2007/rif#constIRI> ) (object  ?iristring ))
	=>
 (bind ?clipsnode   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsnode )))(assert(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/as-expression> ) (object  ?clipsnode )))(assert(TripleTemplate (subject  ?clipsnode ) (predicate  <http://clips.script/symbol> ) (object  (<http://white.gobo/iri-to-clipsconstant> ?iristring  ))))(assert(TripleTemplate (subject  ?clipsnode ) (predicate  <http://example.com/as-constraint-needs-additional-conditionals> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>)))))

(defrule rule85 (declare (salience 60))
(Member (class  <http://www.w3.org/2007/rif#Document> ) (instance  ?rifdocument ))
(TripleTemplate (subject  ?rifdocument ) (predicate  <http://example.com/inherits-data> ) (object  ?riflocal ))
(TripleTemplate (subject  ?riflocal ) (predicate  <http://www.w3.org/2007/rif#constname> ) (object  ?name ))
	=>
 (bind ?clipsnode   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?riflocal ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsnode )))(assert(TripleTemplate (subject  ?riflocal ) (predicate  <http://example.com/as-expression> ) (object  ?clipsnode )))(assert(TripleTemplate (subject  ?clipsnode ) (predicate  <http://clips.script/symbol> ) (object  (<http://white.gobo/local-to-clipsconstant> ?rifdocument   ?name  )))))

(defrule rule86
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/provides-expression> ) (object  ?clipsvar ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://www.w3.org/2007/rif#varname> ) (object  ?varname ))
(TripleTemplate (subject  ?clipspattern ) (predicate  <http://clips.script/constraints> ) (object  ?constraintlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?constraintlist   ?clipsvar  ))

	=>
(assert(Member (instance  ?clipsvar ) (class  <http://clips.script/Variable> )))(assert(TripleTemplate (subject  ?clipsvar ) (predicate  <http://clips.script/variable-name> ) (object  ?varname ))))

(defrule rule87
(Member (class  <http://example.com/Variable> ) (instance  ?factvar ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/provides-expression> ) (object  ?factvar ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://www.w3.org/2007/rif#varname> ) (object  ?varname ))
(not
(exists
(TripleTemplate (subject  ?factvar ) (predicate  <http://clips.script/variable-name> ) (object  ?factname ))
)
)
	=>
(assert(Member (instance  ?factvar ) (class  <http://clips.script/Variable> )))(assert(TripleTemplate (subject  ?factvar ) (predicate  <http://clips.script/variable-name> ) (object  ?varname ))))

(defrule rule88
(Member (class  <http://www.w3.org/2007/rif#Modify> ) (instance  ?rifmodify ))
(TripleTemplate (subject  ?rifmodify ) (predicate  <http://www.w3.org/2007/rif#target> ) (object  ?clause ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?clause ))
(TripleTemplate (subject  ?clause ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?rifobject ))
(TripleTemplate (subject  ?rifobject ) (predicate  <http://example.com/as-expression> ) (object  ?subjterm ))
	=>
 (bind ?clipsassert   (<http://white.gobo/new-blanknode>) ) (bind ?slotsubj   (<http://white.gobo/new-blanknode>) ) (bind ?clipsretractvar   (<http://white.gobo/new-blanknode>) ) (bind ?tripletemplate   (<http://white.gobo/new-blanknode>) ) (bind ?comparesubjectandpredicate   (<http://white.gobo/new-blanknode>) ) (bind ?comparepredicate   (<http://white.gobo/new-blanknode>) ) (bind ?tmpvar   (<http://white.gobo/new-blanknode>) ) (bind ?clipsretractall   (<http://white.gobo/new-blanknode>) ) (bind ?comparesubject   (<http://white.gobo/new-blanknode>) )(assert(Member (instance  ?tmpvar ) (class  <http://clips.script/Variable> )))(assert(TripleTemplate (subject  ?clause ) (predicate  <http://example.com/as-expression> ) (object  ?tmpvar )))(assert(TripleTemplate (subject  ?rifmodify ) (predicate  <http://example.com/as-action> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?clipsretractall   ?clipsassert  ))))(assert(Member (instance  ?clipsretractall ) (class  <http://clips.script/DoForAllFacts> )))(assert(TripleTemplate (subject  ?clipsretractall ) (predicate  <http://clips.script/fact-set-template> ) (object  ?tripletemplate )))(assert(TripleTemplate (subject  ?tripletemplate ) (predicate  <http://clips.script/deftemplate-name> ) (object  "TripleTemplate" )))(assert(TripleTemplate (subject  ?tripletemplate ) (predicate  <http://clips.script/fact-set-member-variable> ) (object  ?tmpvar )))(assert(TripleTemplate (subject  ?clipsretractall ) (predicate  <http://clips.script/query> ) (object  ?comparesubjectandpredicate )))(assert(TripleTemplate (subject  ?comparesubjectandpredicate ) (predicate  <http://clips.script/function-name> ) (object  "and" )))(assert(TripleTemplate (subject  ?comparesubjectandpredicate ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?comparesubject   ?comparepredicate  ))))(assert(TripleTemplate (subject  ?comparesubject ) (predicate  <http://clips.script/function-name> ) (object  "eq" )))(assert(TripleTemplate (subject  ?comparesubject ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?slotsubj   ?subjterm  ))))(assert(TripleTemplate (subject  ?slotsubj ) (predicate  <http://clips.script/member-variable> ) (object  ?tmpvar )))(assert(TripleTemplate (subject  ?slotsubj ) (predicate  <http://clips.script/member-slot-name> ) (object  "subject" )))(assert(TripleTemplate (subject  ?comparepredicate ) (predicate  <http://clips.script/function-name> ) (object  "or" )))(assert(TripleTemplate (subject  ?comparepredicate ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>))))(assert(TripleTemplate (subject  ?comparepredicate ) (predicate  <http://example.com/compare-slotkeys-varpredicate-rifframe> ) (object  ?clause )))(assert(TripleTemplate (subject  ?comparepredicate ) (predicate  <http://example.com/compare-slotkeys-varpredicate-tmpvar> ) (object  ?tmpvar )))(assert(TripleTemplate (subject  ?comparepredicate ) (predicate  <http://example.com/add-compare-predicate-from> ) (object  ?clause )))(assert(TripleTemplate (subject  ?clipsretractall ) (predicate  <http://clips.script/action> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?clipsretractvar  ))))(assert(TripleTemplate (subject  ?clipsretractvar ) (predicate  <http://clips.script/function-name> ) (object  "retract" )))(assert(TripleTemplate (subject  ?clipsretractvar ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?tmpvar  ))))(assert(TripleTemplate (subject  ?clipsassert ) (predicate  <http://example.com/assert-uses-pattern-from> ) (object  ?clause ))))

(defrule rule89
(Member (class  <http://www.w3.org/2007/rif#Assert> ) (instance  ?rifassert ))
(TripleTemplate (subject  ?rifassert ) (predicate  <http://www.w3.org/2007/rif#target> ) (object  ?clause ))
(or
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?clause ))
(Member (class  <http://www.w3.org/2007/rif#SubClass> ) (instance  ?clause ))
(Member (class  <http://www.w3.org/2007/rif#Member> ) (instance  ?clause ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?clause ))
)
	=>
 (bind ?clipsaction   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifassert ) (predicate  <http://example.com/as-action> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?clipsaction  ))))(assert(TripleTemplate (subject  ?clipsaction ) (predicate  <http://example.com/assert-uses-pattern-from> ) (object  ?clause ))))

(defrule rule90
(Member (class  <http://www.w3.org/2007/rif#Retract> ) (instance  ?rifretract ))
(TripleTemplate (subject  ?rifretract ) (predicate  <http://www.w3.org/2007/rif#target> ) (object  ?rifterm ))
(TripleTemplate (subject  ?rifterm ) (predicate  <http://example.com/as-expression> ) (object  ?clipsterm ))
	=>
 (bind ?expandtriples   (<http://white.gobo/new-blanknode>) ) (bind ?slotsubj   (<http://white.gobo/new-blanknode>) ) (bind ?findtriples   (<http://white.gobo/new-blanknode>) ) (bind ?triplequery   (<http://white.gobo/new-blanknode>) ) (bind ?tripletemplate   (<http://white.gobo/new-blanknode>) ) (bind ?clipsretract   (<http://white.gobo/new-blanknode>) ) (bind ?tmpvar   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifretract ) (predicate  <http://example.com/as-action> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?clipsretract  ))))(assert(TripleTemplate (subject  ?clipsretract ) (predicate  <http://clips.script/function-name> ) (object  "retract" )))(assert(TripleTemplate (subject  ?clipsretract ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?expandtriples  ))))(assert(TripleTemplate (subject  ?expandtriples ) (predicate  <http://clips.script/function-name> ) (object  "expand%24" )))(assert(TripleTemplate (subject  ?expandtriples ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?findtriples  ))))(assert(Member (instance  ?findtriples ) (class  <http://clips.script/FindAllFacts> )))(assert(TripleTemplate (subject  ?findtriples ) (predicate  <http://clips.script/fact-set-template> ) (object  ?tripletemplate )))(assert(TripleTemplate (subject  ?findtriples ) (predicate  <http://clips.script/query> ) (object  ?triplequery )))(assert(TripleTemplate (subject  ?tripletemplate ) (predicate  <http://clips.script/deftemplate-name> ) (object  "TripleTemplate" )))(assert(TripleTemplate (subject  ?tripletemplate ) (predicate  <http://clips.script/fact-set-member-variable> ) (object  ?tmpvar )))(assert(TripleTemplate (subject  ?triplequery ) (predicate  <http://clips.script/function-name> ) (object  "eq" )))(assert(TripleTemplate (subject  ?triplequery ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?clipsterm   ?slotsubj  ))))(assert(TripleTemplate (subject  ?slotsubj ) (predicate  <http://clips.script/member-variable> ) (object  ?tmpvar )))(assert(TripleTemplate (subject  ?slotsubj ) (predicate  <http://clips.script/member-slot-name> ) (object  "subject" )))(assert(Member (instance  ?tmpvar ) (class  <http://clips.script/Variable> )))(assert(Member (instance  ?tmpvar ) (class  <http://example.com/Variable> ))))

(defrule rule91
(or
(Member (class  <http://www.w3.org/2007/rif#Member> ) (instance  ?clause ))
(Member (class  <http://www.w3.org/2007/rif#SubClass> ) (instance  ?clause ))
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?clause ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?clause ))
)
(or
(TripleTemplate (subject  ?rifrule ) (predicate  <http://www.w3.org/2007/rif#formula> ) (object  ?clause ))
(TripleTemplate (subject  ?rifrule ) (predicate  <http://www.w3.org/2007/rif#then> ) (object  ?clause ))
)
	=>
 (bind ?clipsaction   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?clause ) (predicate  <http://example.com/as-action> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?clipsaction  ))))(assert(TripleTemplate (subject  ?clipsaction ) (predicate  <http://example.com/assert-uses-pattern-from> ) (object  ?clause ))))

(defrule rule92
(Member (class  <http://white.gobo/modelA#RHSPatternGenerator> ) (instance  ?rifsuperclass ))
(TripleTemplate (subject  ?rifsuperclass ) (predicate  <http://www.w3.org/2007/rif#sub> ) (object  ?sub ))
(TripleTemplate (subject  ?rifsuperclass ) (predicate  <http://www.w3.org/2007/rif#super> ) (object  ?super ))
(TripleTemplate (subject  ?sub ) (predicate  <http://example.com/as-expression> ) (object  ?expressionsub ))
(TripleTemplate (subject  ?super ) (predicate  <http://example.com/as-expression> ) (object  ?expressionsuper ))
	=>
 (bind ?slotsub   (<http://white.gobo/new-blanknode>) ) (bind ?slotsuper   (<http://white.gobo/new-blanknode>) ) (bind ?rhspattern   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifsuperclass ) (predicate  <http://example.com/as-rhspattern> ) (object  ?rhspattern )))(assert(TripleTemplate (subject  ?rhspattern ) (predicate  <http://clips.script/deftemplate-name> ) (object  "Subclass" )))(assert(TripleTemplate (subject  ?rhspattern ) (predicate  <http://clips.script/slot> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?slotsub   ?slotsuper  ))))(assert(TripleTemplate (subject  ?slotsub ) (predicate  <http://clips.script/slot-name> ) (object  "sub" )))(assert(TripleTemplate (subject  ?slotsub ) (predicate  <http://clips.script/field> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?expressionsub  ))))(assert(TripleTemplate (subject  ?slotsuper ) (predicate  <http://clips.script/slot-name> ) (object  "super" )))(assert(TripleTemplate (subject  ?slotsuper ) (predicate  <http://clips.script/field> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?expressionsuper  )))))

(defrule rule93 (declare (salience 10))
(TripleTemplate (subject  ?slotargs ) (predicate  <http://example.com/add-atom-args-rhspattern> ) (object  ?list ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#numeric-equal> "0^^http://www.w3.org/2001/XMLSchema#integer"   (<http://www.w3.org/2007/rif-builtin-function#count> ?list  ) ))

	=>
 (retract(assert(TripleTemplate (subject  ?slotargs ) (predicate  <http://example.com/add-atom-args-rhspattern> ) (object  ?list ))) ))

(defrule rule94
(Member (class  <http://white.gobo/modelA#RHSPatternGenerator> ) (instance  ?rifatom ))
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?op ))
(TripleTemplate (subject  ?op ) (predicate  <http://example.com/as-expression> ) (object  ?expressionop ))
(not
(exists
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
)
)
	=>
 (bind ?slotop   (<http://white.gobo/new-blanknode>) ) (bind ?rhspattern   (<http://white.gobo/new-blanknode>) ) (bind ?slotargs   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifatom ) (predicate  <http://example.com/as-rhspattern> ) (object  ?rhspattern )))(assert(TripleTemplate (subject  ?rhspattern ) (predicate  <http://clips.script/deftemplate-name> ) (object  "Atom" )))(assert(TripleTemplate (subject  ?rhspattern ) (predicate  <http://clips.script/slot> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?slotop   ?slotargs  ))))(assert(TripleTemplate (subject  ?slotop ) (predicate  <http://clips.script/slot-name> ) (object  "op" )))(assert(TripleTemplate (subject  ?slotop ) (predicate  <http://clips.script/field> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?expressionop  ))))(assert(TripleTemplate (subject  ?slotargs ) (predicate  <http://clips.script/slot-name> ) (object  "args" )))(assert(TripleTemplate (subject  ?slotargs ) (predicate  <http://clips.script/field> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>)))))

(defrule rule95
(Member (class  <http://www.w3.org/2007/rif#Retract> ) (instance  ?rifretract ))
(TripleTemplate (subject  ?rifretract ) (predicate  <http://www.w3.org/2007/rif#target> ) (object  ?clause ))
(or
(Member (class  <http://www.w3.org/2007/rif#Member> ) (instance  ?clause ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?clause ))
(Member (class  <http://www.w3.org/2007/rif#SubClass> ) (instance  ?clause ))
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?clause ))
)
	=>
 (bind ?clipsaction   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifretract ) (predicate  <http://example.com/as-action> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?clipsaction  ))))(assert(TripleTemplate (subject  ?clipsaction ) (predicate  <http://clips.script/function-name> ) (object  "retract" )))(assert(TripleTemplate (subject  ?clipsaction ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>))))(assert(TripleTemplate (subject  ?clipsaction ) (predicate  <http://example.com/retract-uses-pattern-from> ) (object  ?clause ))))

(defrule rule96
(Member (class  <http://white.gobo/modelA#RHSPatternGenerator> ) (instance  ?rifmember ))
(TripleTemplate (subject  ?rifmember ) (predicate  <http://www.w3.org/2007/rif#class> ) (object  ?cls ))
(TripleTemplate (subject  ?rifmember ) (predicate  <http://www.w3.org/2007/rif#instance> ) (object  ?instance ))
(TripleTemplate (subject  ?cls ) (predicate  <http://example.com/as-expression> ) (object  ?expressioncls ))
(TripleTemplate (subject  ?instance ) (predicate  <http://example.com/as-expression> ) (object  ?expressioninstance ))
	=>
 (bind ?rhspattern   (<http://white.gobo/new-blanknode>) ) (bind ?slotinstance   (<http://white.gobo/new-blanknode>) ) (bind ?slotcls   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifmember ) (predicate  <http://example.com/as-rhspattern> ) (object  ?rhspattern )))(assert(TripleTemplate (subject  ?rhspattern ) (predicate  <http://clips.script/deftemplate-name> ) (object  "Member" )))(assert(TripleTemplate (subject  ?rhspattern ) (predicate  <http://clips.script/slot> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?slotinstance   ?slotcls  ))))(assert(TripleTemplate (subject  ?slotinstance ) (predicate  <http://clips.script/slot-name> ) (object  "instance" )))(assert(TripleTemplate (subject  ?slotinstance ) (predicate  <http://clips.script/field> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?expressioninstance  ))))(assert(TripleTemplate (subject  ?slotcls ) (predicate  <http://clips.script/slot-name> ) (object  "class" )))(assert(TripleTemplate (subject  ?slotcls ) (predicate  <http://clips.script/field> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?expressioncls  )))))

(defrule rule97
(TripleTemplate (subject  ?clipsretract ) (predicate  <http://example.com/retract-uses-pattern-from> ) (object  ?rifformula ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://example.com/as-rhspattern> ) (object  ?rhspattern ))
	=>
 (bind ?retracttargets   (do-for-fact (( ?fct2 TripleTemplate)) (and (eq ?fct2:subject   ?clipsretract  )  (eq ?fct2:predicate   <http://clips.script/function-args>  ) ) (fact-slot-value ?fct2   object  ) )  ) (bind ?clipsassert   (<http://white.gobo/new-blanknode>) ) (do-for-all-facts (( ?fct32 TripleTemplate)) (and (eq ?fct32:subject   ?clipsretract  )  (eq ?fct32:predicate   <http://clips.script/function-args>  ) ) (retract ?fct32  ) ) (assert(TripleTemplate (subject  ?clipsretract ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?retracttargets   ?clipsassert  ))))(assert(TripleTemplate (subject  ?clipsassert ) (predicate  <http://clips.script/assert> ) (object  ?rhspattern ))))

(defrule rule98
(TripleTemplate (subject  ?clipsassert ) (predicate  <http://example.com/assert-uses-pattern-from> ) (object  ?rifformula ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://example.com/as-rhspattern> ) (object  ?rhspattern ))
	=>
(assert(TripleTemplate (subject  ?clipsassert ) (predicate  <http://clips.script/assert> ) (object  ?rhspattern ))))

(defrule rule99 (declare (salience -100))
(TripleTemplate (subject  ?clipsfunction ) (predicate  <http://example.com/add-atom-args-rhspattern> ) (object  ?rifrestargs ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#numeric-not-equal> "0^^http://www.w3.org/2001/XMLSchema#integer"   (<http://www.w3.org/2007/rif-builtin-function#count> ?rifrestargs  ) ))

	=>
(assert(Member (instance  ?clipsfunction ) (class  <http://example.com/cant-translate-atom-as-rhspattern> ))) (<http://white.gobo/set-graph-in-errorstate> "Translation%20of%20rif%3AAtom%20to%20rhs-pattern%20failed.%20Didnt%20translated%20all%20rif%3Aargs.%28ex%3Acant-translate-atom-as-rhspattern%29"  ))

(defrule rule100
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?slotkey ))
(TripleTemplate (subject  ?slotkey ) (predicate  <http://example.com/as-expression> ) (object  ?slotkeyterm ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?slotlist  ))

(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

(test (eq "1^^http://www.w3.org/2001/XMLSchema#integer"   (<http://www.w3.org/2007/rif-builtin-function#count> ?slotlist  ) ))

(TripleTemplate (subject  ?comparepredicate ) (predicate  <http://example.com/compare-slotkeys-varpredicate-rifframe> ) (object  ?rifframe ))
(TripleTemplate (subject  ?comparepredicate ) (predicate  <http://example.com/compare-slotkeys-varpredicate-tmpvar> ) (object  ?tmpvar ))
	=>
 (bind ?slotpred   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?slotpred ) (predicate  <http://clips.script/member-variable> ) (object  ?tmpvar )))(assert(TripleTemplate (subject  ?slotpred ) (predicate  <http://clips.script/member-slot-name> ) (object  "predicate" ))) (do-for-all-facts (( ?fct30 TripleTemplate)) (and (eq ?fct30:subject   ?comparepredicate  )  (eq ?fct30:predicate   <http://clips.script/function-name>  ) ) (retract ?fct30  ) ) (assert(TripleTemplate (subject  ?comparepredicate ) (predicate  <http://clips.script/function-name> ) (object  "eq" ))) (do-for-all-facts (( ?fct31 TripleTemplate)) (and (eq ?fct31:subject   ?comparepredicate  )  (eq ?fct31:predicate   <http://clips.script/function-args>  ) ) (retract ?fct31  ) ) (assert(TripleTemplate (subject  ?comparepredicate ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?slotpred   ?slotkeyterm  )))))

(defrule rule101
(Member (class  <http://white.gobo/modelA#RHSPatternGenerator> ) (instance  ?rifnode ))
(TripleTemplate (subject  ?rifnode ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?object ))
(TripleTemplate (subject  ?rifnode ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?slotlist  ))

(TripleTemplate (subject  ?object ) (predicate  <http://example.com/as-expression> ) (object  ?expressionsubject ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?slotkey ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

(TripleTemplate (subject  ?slotkey ) (predicate  <http://example.com/as-expression> ) (object  ?expressionpredicate ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?slotvalue ))
(TripleTemplate (subject  ?slotvalue ) (predicate  <http://example.com/as-expression> ) (object  ?expressionobject ))
	=>
 (bind ?slotsubject   (<http://white.gobo/new-blanknode>) ) (bind ?slotpredicate   (<http://white.gobo/new-blanknode>) ) (bind ?rhspattern   (<http://white.gobo/new-blanknode>) ) (bind ?slotobject   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/as-rhspattern> ) (object  ?rhspattern )))(assert(TripleTemplate (subject  ?rhspattern ) (predicate  <http://clips.script/deftemplate-name> ) (object  "TripleTemplate" )))(assert(TripleTemplate (subject  ?rhspattern ) (predicate  <http://clips.script/slot> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?slotsubject   ?slotpredicate   ?slotobject  ))))(assert(TripleTemplate (subject  ?slotsubject ) (predicate  <http://clips.script/slot-name> ) (object  "subject" )))(assert(TripleTemplate (subject  ?slotsubject ) (predicate  <http://clips.script/field> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?expressionsubject  ))))(assert(TripleTemplate (subject  ?slotpredicate ) (predicate  <http://clips.script/slot-name> ) (object  "predicate" )))(assert(TripleTemplate (subject  ?slotpredicate ) (predicate  <http://clips.script/field> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?expressionpredicate  ))))(assert(TripleTemplate (subject  ?slotobject ) (predicate  <http://clips.script/slot-name> ) (object  "object" )))(assert(TripleTemplate (subject  ?slotobject ) (predicate  <http://clips.script/field> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?expressionobject  )))))

(defrule rule102
(Member (class  <http://white.gobo/modelA#RHSPatternGenerator> ) (instance  ?rifatom ))
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?arglist  ))

(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?op ))
(TripleTemplate (subject  ?op ) (predicate  <http://example.com/as-expression> ) (object  ?expressionop ))
	=>
 (bind ?rhspattern   (<http://white.gobo/new-blanknode>) ) (bind ?slotargs   (<http://white.gobo/new-blanknode>) ) (bind ?slotop   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifatom ) (predicate  <http://example.com/as-rhspattern> ) (object  ?rhspattern )))(assert(TripleTemplate (subject  ?rhspattern ) (predicate  <http://clips.script/deftemplate-name> ) (object  "Atom" )))(assert(TripleTemplate (subject  ?rhspattern ) (predicate  <http://clips.script/slot> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?slotop   ?slotargs  ))))(assert(TripleTemplate (subject  ?slotop ) (predicate  <http://clips.script/slot-name> ) (object  "op" )))(assert(TripleTemplate (subject  ?slotop ) (predicate  <http://clips.script/field> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?expressionop  ))))(assert(TripleTemplate (subject  ?slotargs ) (predicate  <http://clips.script/slot-name> ) (object  "args" )))(assert(TripleTemplate (subject  ?slotargs ) (predicate  <http://clips.script/field> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>))))(assert(TripleTemplate (subject  ?slotargs ) (predicate  <http://example.com/add-atom-args-rhspattern> ) (object  ?arglist ))))

(defrule rule103 (declare (salience 10))
(TripleTemplate (subject  ?slotargs ) (predicate  <http://example.com/add-atom-args-rhspattern> ) (object  ?arglist ))
(TripleTemplate (subject  = (<http://www.w3.org/2007/rif-builtin-function#get> ?arglist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )) (predicate  <http://example.com/as-expression> ) (object  ?clipsexpr ))
	=>
 (bind ?oldfield   (do-for-fact (( ?fct3 TripleTemplate)) (and (eq ?fct3:subject   ?slotargs  )  (eq ?fct3:predicate   <http://clips.script/field>  ) ) (fact-slot-value ?fct3   object  ) )  ) (do-for-all-facts (( ?fct28 TripleTemplate)) (and (eq ?fct28:subject   ?slotargs  )  (eq ?fct28:predicate   <http://example.com/add-atom-args-rhspattern>  ) ) (retract ?fct28  ) ) (assert(TripleTemplate (subject  ?slotargs ) (predicate  <http://example.com/add-atom-args-rhspattern> ) (object  (<http://www.w3.org/2007/rif-builtin-function#remove> ?arglist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )))) (do-for-all-facts (( ?fct29 TripleTemplate)) (and (eq ?fct29:subject   ?slotargs  )  (eq ?fct29:predicate   <http://clips.script/field>  ) ) (retract ?fct29  ) ) (assert(TripleTemplate (subject  ?slotargs ) (predicate  <http://clips.script/field> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?oldfield   ?clipsexpr  )))))

(defrule rule104
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?item ))
(TripleTemplate (subject  ?item ) (predicate  <http://example.com/as-constraint> ) (object  ?term ))
(TripleTemplate (subject  ?items ) (predicate  <http://clips.script/constraints> ) (object  ?oldlist ))
(TripleTemplate (subject  ?items ) (predicate  <http://white.gobo/local/b/nfc895320_n5722#add-additional-patterns-to> ) (object  ?multipattern ))
(TripleTemplate (subject  ?items ) (predicate  <http://white.gobo/local/b/nfc895320_n5722#add-item-from> ) (object  ?rifitems ))
(test (eq ?item   (<http://www.w3.org/2007/rif-builtin-function#get> ?rifitems   "0^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

	=>
 (do-for-all-facts (( ?fct37 TripleTemplate)) (and (eq ?fct37:subject   ?items  )  (eq ?fct37:predicate   <http://white.gobo/local/b/nfc895320_n5722#add-item-from>  ) ) (retract ?fct37  ) ) (assert(TripleTemplate (subject  ?items ) (predicate  <http://white.gobo/local/b/nfc895320_n5722#add-item-from> ) (object  (<http://www.w3.org/2007/rif-builtin-function#remove> ?rifitems   "0^^http://www.w3.org/2001/XMLSchema#integer"  )))) (do-for-all-facts (( ?fct36 TripleTemplate)) (and (eq ?fct36:subject   ?items  )  (eq ?fct36:predicate   <http://clips.script/constraints>  ) ) (retract ?fct36  ) ) (assert(TripleTemplate (subject  ?items ) (predicate  <http://clips.script/constraints> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?oldlist   ?term  ))))(assert(TripleTemplate (subject  ?multipattern ) (predicate  <http://white.gobo/local/b/nfc895320_n5722#add-list> ) (object  ?item ))))

(defrule rule105
(or
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?item ))
(Member (class  <http://www.w3.org/2007/rif#Const> ) (instance  ?item ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?item ))
)
(TripleTemplate (subject  ?item ) (predicate  <http://example.com/as-constraint> ) (object  ?term ))
(TripleTemplate (subject  ?items ) (predicate  <http://white.gobo/local/b/nfc895320_n5722#add-item-from> ) (object  ?rifitems ))
(test (eq ?item   (<http://www.w3.org/2007/rif-builtin-function#get> ?rifitems   "0^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

(TripleTemplate (subject  ?items ) (predicate  <http://clips.script/constraints> ) (object  ?oldlist ))
	=>
 (do-for-all-facts (( ?fct33 TripleTemplate)) (and (eq ?fct33:subject   ?items  )  (eq ?fct33:predicate   <http://white.gobo/local/b/nfc895320_n5722#add-item-from>  ) ) (retract ?fct33  ) ) (assert(TripleTemplate (subject  ?items ) (predicate  <http://white.gobo/local/b/nfc895320_n5722#add-item-from> ) (object  (<http://www.w3.org/2007/rif-builtin-function#remove> ?rifitems   "0^^http://www.w3.org/2001/XMLSchema#integer"  )))) (do-for-all-facts (( ?fct34 TripleTemplate)) (and (eq ?fct34:subject   ?items  )  (eq ?fct34:predicate   <http://clips.script/constraints>  ) ) (retract ?fct34  ) ) (assert(TripleTemplate (subject  ?items ) (predicate  <http://clips.script/constraints> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?oldlist   ?term  )))))

(defrule rule106
(TripleTemplate (subject  ?list ) (predicate  <http://www.w3.org/2007/rif#rest> ) (object  ?rest ))
(TripleTemplate (subject  ?items ) (predicate  <http://white.gobo/local/b/nfc895320_n5722#use-items-from> ) (object  ?list ))
(TripleTemplate (subject  ?items ) (predicate  <http://white.gobo/local/b/nfc895320_n5722#add-item-from> ) (object  ?rifitems ))
(test (eq "0^^http://www.w3.org/2001/XMLSchema#integer"   (<http://www.w3.org/2007/rif-builtin-function#count> ?rifitems  ) ))

(TripleTemplate (subject  ?items ) (predicate  <http://clips.script/constraints> ) (object  ?oldlist ))
(not
(test (eq ?rest   (<http://www.w3.org/2007/rif-builtin-function#make-list>) ))

)
(not
(Member (class  <http://white.gobo/local/b/nfc895320_n5722#OpenList> ) (instance  ?items ))
)
	=>
 (bind ?anyslots   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?items ) (predicate  <http://white.gobo/local/b/nfc895320_n5722#added-rest> ) (object  ?rest )))(assert(Member (instance  ?anyslots ) (class  <http://clips.script/MultifieldVariable> )))(assert(TripleTemplate (subject  ?anyslots ) (predicate  <http://clips.script/variable-name> ) (object  "" ))) (do-for-all-facts (( ?fct35 TripleTemplate)) (and (eq ?fct35:subject   ?items  )  (eq ?fct35:predicate   <http://clips.script/constraints>  ) ) (retract ?fct35  ) ) (assert(TripleTemplate (subject  ?items ) (predicate  <http://clips.script/constraints> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?oldlist   ?anyslots  ))))(assert(Member (instance  ?items ) (class  <http://white.gobo/local/b/nfc895320_n5722#OpenList> ))))

(defrule rule107
(Member (class  <http://white.gobo/modelA#AtomPatternGenerator> ) (instance  ?formula ))
(Member (class  <http://white.gobo/modelA#MultiPatternGenerator> ) (instance  ?formula ))
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?formulapattern ))
	=>
 (bind ?andpattern   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#as-multi-lhs-pattern> ) (object  ?andpattern )))(assert(Member (instance  ?andpattern ) (class  <http://clips.script/AndCE> )))(assert(TripleTemplate (subject  ?andpattern ) (predicate  <http://clips.script/conditional-element> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?formulapattern  )))))

(defrule rule108
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rest ))
(TripleTemplate (subject  ?rest ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsvar ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://www.w3.org/2007/rif#rest> ) (object  ?rest ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://www.w3.org/2007/rif#items> ) (object  ?itemlist ))
(TripleTemplate (subject  ?multipattern ) (predicate  <http://white.gobo/local/b/nfc895320_n5722#add-list> ) (object  ?riflist ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/as-constraint> ) (object  ?listvar ))
(not
(Member (class  <http://white.gobo/modelA#VarAsConstExpr> ) (instance  ?clipsvar ))
)
(not
(Member (class  <http://example.com/Variable> ) (instance  ?clipsvar ))
)
	=>
 (bind ?position   (<http://white.gobo/new-blanknode>) ) (bind ?function   (<http://white.gobo/new-blanknode>) )(assert(Member (instance  ?clipsvar ) (class  <http://white.gobo/modelA#VarAsConstExpr> )))(assert(TripleTemplate (subject  ?clipsvar ) (predicate  <http://clips.script/var-as-const-expr> ) (object  ?function )))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-name> ) (object  "%3Chttp%3A%2F%2Fwww.w3.org%2F2007%2Frif-builtin-function%23sublist%3E" )))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?listvar   ?position  ))))(assert(TripleTemplate (subject  ?position ) (predicate  <http://clips.script/string> ) (object  (<http://white.gobo/literal-to-clipsconstant> (<http://www.w3.org/2007/rif-builtin-function#count> ?itemlist  ) )))))

(defrule rule109
(TripleTemplate (subject  ?list ) (predicate  <http://www.w3.org/2007/rif#items> ) (object  ?rifitems ))
(TripleTemplate (subject  ?multipattern ) (predicate  <http://white.gobo/local/b/nfc895320_n5722#add-list> ) (object  ?list ))
(TripleTemplate (subject  ?list ) (predicate  <http://example.com/as-constraint> ) (object  ?listvar ))
(not
(TripleTemplate (subject  ?multipattern ) (predicate  <http://white.gobo/local/b/nfc895320_n5722#added-list> ) (object  ?list ))
)
	=>
 (bind ?checkvar   (<http://white.gobo/new-blanknode>) ) (bind ?pattern   (<http://white.gobo/new-blanknode>) ) (bind ?oldlist   (do-for-fact (( ?fct4 TripleTemplate)) (and (eq ?fct4:subject   ?multipattern  )  (eq ?fct4:predicate   <http://clips.script/conditional-element>  ) ) (fact-slot-value ?fct4   object  ) )  ) (bind ?check   (<http://white.gobo/new-blanknode>) ) (bind ?items   (<http://white.gobo/new-blanknode>) ) (bind ?assign   (<http://white.gobo/new-blanknode>) ) (bind ?checkfunction   (<http://white.gobo/new-blanknode>) )(assert(Member (instance  ?checkvar ) (class  <http://example.com/Variable> )))(assert(Member (instance  ?checkvar ) (class  <http://clips.script/Variable> )))(assert(Member (instance  ?assign ) (class  <http://clips.script/AssignedPatternCE> )))(assert(TripleTemplate (subject  ?assign ) (predicate  <http://clips.script/fact-var-symbol> ) (object  ?checkvar )))(assert(TripleTemplate (subject  ?assign ) (predicate  <http://clips.script/pattern-ce> ) (object  ?pattern )))(assert(Member (instance  ?pattern ) (class  <http://clips.script/TemplatePatternCE> )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/deftemplate-name> ) (object  "AtomList" )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/slot> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?items  ))))(assert(TripleTemplate (subject  ?items ) (predicate  <http://white.gobo/local/b/nfc895320_n5722#add-additional-patterns-to> ) (object  ?multipattern )))(assert(TripleTemplate (subject  ?items ) (predicate  <http://clips.script/slot-name> ) (object  "items" )))(assert(TripleTemplate (subject  ?items ) (predicate  <http://clips.script/constraints> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>))))(assert(TripleTemplate (subject  ?items ) (predicate  <http://white.gobo/local/b/nfc895320_n5722#add-item-from> ) (object  ?rifitems )))(assert(TripleTemplate (subject  ?items ) (predicate  <http://white.gobo/local/b/nfc895320_n5722#use-items-from> ) (object  ?list )))(assert(Member (instance  ?check ) (class  <http://clips.script/TestCE> )))(assert(TripleTemplate (subject  ?check ) (predicate  <http://clips.script/function-call> ) (object  ?checkfunction )))(assert(TripleTemplate (subject  ?checkfunction ) (predicate  <http://clips.script/function-name> ) (object  "eq" )))(assert(TripleTemplate (subject  ?checkfunction ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?checkvar   ?listvar  )))) (do-for-all-facts (( ?fct38 TripleTemplate)) (and (eq ?fct38:subject   ?multipattern  )  (eq ?fct38:predicate   <http://clips.script/conditional-element>  ) ) (retract ?fct38  ) ) (assert(TripleTemplate (subject  ?multipattern ) (predicate  <http://clips.script/conditional-element> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?oldlist   ?assign   ?check  ))))(assert(TripleTemplate (subject  ?multipattern ) (predicate  <http://white.gobo/local/b/nfc895320_n5722#added-list> ) (object  ?list ))))

(defrule rule110
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rest ))
(TripleTemplate (subject  ?list ) (predicate  <http://www.w3.org/2007/rif#rest> ) (object  ?rest ))
(TripleTemplate (subject  ?rest ) (predicate  <http://example.com/as-constraint> ) (object  ?clipsvar ))
(TripleTemplate (subject  ?multipattern ) (predicate  <http://white.gobo/local/b/nfc895320_n5722#add-list> ) (object  ?list ))
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#binds-var> ) (object  ?clipsvar ))
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#as-multi-lhs-pattern> ) (object  ?multipattern ))
(or
(Member (class  <http://white.gobo/modelA#VarAsConstExpr> ) (instance  ?clipsvar ))
(Member (class  <http://example.com/Variable> ) (instance  ?clipsvar ))
)
(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/as-expression> ) (object  ?listvar ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://www.w3.org/2007/rif#items> ) (object  ?itemlist ))
	=>
 (bind ?position   (<http://white.gobo/new-blanknode>) ) (bind ?rightexpr   (<http://white.gobo/new-blanknode>) ) (bind ?leftexpr   (<http://white.gobo/new-blanknode>) ) (bind ?eq   (<http://white.gobo/new-blanknode>) ) (bind ?testpattern   (<http://white.gobo/new-blanknode>) )(assert(Member (instance  ?testpattern ) (class  <http://clips.script/TestCE> )))(assert(TripleTemplate (subject  ?testpattern ) (predicate  <http://clips.script/function-call> ) (object  ?eq )))(assert(TripleTemplate (subject  ?eq ) (predicate  <http://clips.script/function-name> ) (object  "eq" )))(assert(TripleTemplate (subject  ?eq ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?clipsvar   ?rightexpr  ))))(assert(TripleTemplate (subject  ?rightexpr ) (predicate  <http://clips.script/function-name> ) (object  "%3Chttp%3A%2F%2Fwww.w3.org%2F2007%2Frif-builtin-function%23sublist%3E" )))(assert(TripleTemplate (subject  ?rightexpr ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?listvar   ?position  ))))(assert(TripleTemplate (subject  ?position ) (predicate  <http://clips.script/string> ) (object  (<http://white.gobo/literal-to-clipsconstant> (<http://www.w3.org/2007/rif-builtin-function#count> ?itemlist  ) )))))

(defrule rule111
(Member (class  <http://white.gobo/modelA#MultiPatternGenerator> ) (instance  ?formula ))
(Member (class  <http://white.gobo/modelA#AtomPatternGenerator> ) (instance  ?formula ))
(TripleTemplate (subject  ?formula ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#as-multi-lhs-pattern> ) (object  ?andpattern ))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?list ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?arglist   ?list  ))

	=>
(assert(TripleTemplate (subject  ?andpattern ) (predicate  <http://white.gobo/local/b/nfc895320_n5722#add-list> ) (object  ?list ))))

(defrule rule112
(Member (class  <http://white.gobo/modelA#MultiPatternGenerator> ) (instance  ?formula ))
(Member (class  <http://white.gobo/modelA#TripleTemplateGenerator> ) (instance  ?formula ))
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?formulapattern ))
(TripleTemplate (subject  ?formula ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?list ))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?list ))
	=>
 (bind ?andpattern   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#as-multi-lhs-pattern> ) (object  ?andpattern )))(assert(Member (instance  ?andpattern ) (class  <http://clips.script/AndCE> )))(assert(TripleTemplate (subject  ?andpattern ) (predicate  <http://clips.script/conditional-element> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?formulapattern  ))))(assert(TripleTemplate (subject  ?andpattern ) (predicate  <http://white.gobo/local/b/nfc895320_n5722#add-list> ) (object  ?list ))))

(defrule rule113
(Member (class  <http://www.w3.org/2007/rif#Execute> ) (instance  ?rifexecute ))
(TripleTemplate (subject  ?rifexecute ) (predicate  <http://www.w3.org/2007/rif#target> ) (object  ?target ))
(TripleTemplate (subject  ?target ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?rifop ))
(TripleTemplate (subject  ?target ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?rifarglist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?rifarglist  ))

(TripleTemplate (subject  ?rifop ) (predicate  <http://example.com/as-expression> ) (object  ?functionsymbol ))
(TripleTemplate (subject  ?functionsymbol ) (predicate  <http://clips.script/symbol> ) (object  ?functionname ))
	=>
 (bind ?function   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifexecute ) (predicate  <http://example.com/as-action> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?function  ))))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-name> ) (object  ?functionname )))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>))))(assert(TripleTemplate (subject  ?function ) (predicate  <http://white.gobo/local/b/nfc895320_n5034#add-args-from> ) (object  ?rifarglist ))))

(defrule rule114 (declare (salience 15))
(TripleTemplate (subject  ?firstarg ) (predicate  <http://example.com/as-expression> ) (object  ?clipsexpression ))
(TripleTemplate (subject  ?function ) (predicate  <http://white.gobo/local/b/nfc895320_n5034#add-args-from> ) (object  ?rifarglist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?rifarglist  ))

(test (eq ?firstarg   (<http://www.w3.org/2007/rif-builtin-function#get> ?rifarglist   "0^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

	=>
 (bind ?functionargs   (do-for-fact (( ?fct5 TripleTemplate)) (and (eq ?fct5:subject   ?function  )  (eq ?fct5:predicate   <http://clips.script/function-args>  ) ) (fact-slot-value ?fct5   object  ) )  ) (do-for-all-facts (( ?fct40 TripleTemplate)) (and (eq ?fct40:subject   ?function  )  (eq ?fct40:predicate   <http://clips.script/function-args>  ) ) (retract ?fct40  ) ) (assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?functionargs   ?clipsexpression  )))) (do-for-all-facts (( ?fct39 TripleTemplate)) (and (eq ?fct39:subject   ?function  )  (eq ?fct39:predicate   <http://white.gobo/local/b/nfc895320_n5034#add-args-from>  ) ) (retract ?fct39  ) ) (assert(TripleTemplate (subject  ?function ) (predicate  <http://white.gobo/local/b/nfc895320_n5034#add-args-from> ) (object  (<http://www.w3.org/2007/rif-builtin-function#remove> ?rifarglist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )))))

(defrule rule115 (declare (salience 1000))
(TripleTemplate (subject  ?directive ) (predicate  <http://www.w3.org/2007/rif#profile> ) (object  ?profile ))
(TripleTemplate (subject  ?directive ) (predicate  <http://www.w3.org/2007/rif#location> ) (object  ?location ))
	=>
 (<http://white.gobo/import> ?location   ?profile  ))

(defrule rule116 (declare (salience 1000))
(TripleTemplate (subject  ?directive ) (predicate  <http://www.w3.org/2007/rif#location> ) (object  ?location ))
(not
(exists
(TripleTemplate (subject  ?directive ) (predicate  <http://www.w3.org/2007/rif#profile> ) (object  ?profile ))
)
)
	=>
(assert(TripleTemplate (subject  ?directive ) (predicate  <http://www.w3.org/2007/rif#profile> ) (object  <http://www.w3.org/ns/entailment/RIF> ))))

(defrule rule117 (declare (salience 10))
(Member (class  <http://white.gobo/modelA#ConstraintGenerator> ) (instance  ?riflist ))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?riflist ))
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#pattern-uses-constraint> ) (object  ?riflist ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://www.w3.org/2007/rif#rest> ) (object  ?rest ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://www.w3.org/2007/rif#items> ) (object  ?itemlist ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/as-constraint> ) (object  ?listvar ))
(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#bound-variable> ) (object  ?assign ))
(TripleTemplate (subject  ?rest ) (predicate  <http://example.com/as-constraint> ) (object  ?assign ))
	=>
 (bind ?eq   (<http://white.gobo/new-blanknode>) ) (bind ?position   (<http://white.gobo/new-blanknode>) ) (bind ?function   (<http://white.gobo/new-blanknode>) ) (bind ?testpattern   (<http://white.gobo/new-blanknode>) )(assert(Member (instance  ?testpattern ) (class  <http://clips.script/TestCE> )))(assert(TripleTemplate (subject  ?testpattern ) (predicate  <http://clips.script/function-call> ) (object  ?eq )))(assert(TripleTemplate (subject  ?formula ) (predicate  <http://white.gobo/modelA#lhs-pattern-after-conditions> ) (object  ?testpattern )))(assert(TripleTemplate (subject  ?eq ) (predicate  <http://clips.script/function-name> ) (object  "eq" )))(assert(TripleTemplate (subject  ?eq ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?assign   ?function  ))))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-name> ) (object  "%3Chttp%3A%2F%2Fwww.w3.org%2F2007%2Frif-builtin-function%23sublist%3E" )))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?listvar   ?position  ))))(assert(TripleTemplate (subject  ?position ) (predicate  <http://clips.script/string> ) (object  (<http://white.gobo/literal-to-clipsconstant> (<http://www.w3.org/2007/rif-builtin-function#count> ?itemlist  ) )))))

(defrule rule118 (declare (salience -1))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?riflist ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/as-constraint> ) (object  ?listasvar ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/as-lhs-pattern> ) (object  ?pattern ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/add-as-pattern> ) (object  ?defrule ))
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
(not
(TripleTemplate (subject  ?defrule ) (predicate  <http://example.com/bound-variable> ) (object  ?listasvar ))
)
(not
(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/used-as-pattern-in> ) (object  ?defrule ))
)
	=>
 (bind ?assignpattern   (<http://white.gobo/new-blanknode>) ) (bind ?oldpatternlist   (do-for-fact (( ?fct7 TripleTemplate)) (and (eq ?fct7:subject   ?defrule  )  (eq ?fct7:predicate   <http://clips.script/conditional-element>  ) ) (fact-slot-value ?fct7   object  ) )  )(assert(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/used-as-pattern-in> ) (object  ?defrule )))(assert(Member (instance  ?assignpattern ) (class  <http://clips.script/AssignedPatternCE> )))(assert(TripleTemplate (subject  ?assignpattern ) (predicate  <http://clips.script/pattern-ce> ) (object  ?pattern )))(assert(TripleTemplate (subject  ?assignpattern ) (predicate  <http://clips.script/fact-var-symbol> ) (object  ?listasvar ))) (do-for-all-facts (( ?fct46 TripleTemplate)) (and (eq ?fct46:subject   ?defrule  )  (eq ?fct46:predicate   <http://clips.script/conditional-element>  ) ) (retract ?fct46  ) ) (assert(TripleTemplate (subject  ?defrule ) (predicate  <http://clips.script/conditional-element> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?oldpatternlist   ?assignpattern  ))))(assert(TripleTemplate (subject  ?defrule ) (predicate  <http://example.com/transfer-bound-variables-from> ) (object  ?pattern ))))

(defrule rule119 (declare (salience 10))
(TripleTemplate (subject  ?riflist ) (predicate  <http://www.w3.org/2007/rif#rest> ) (object  ?rest ))
(not
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rest ))
)
	=>
 (<http://white.gobo/set-graph-in-errorstate> "rif%3Arest%20is%20only%20implemented%20for%20domain%20of%20type%20rif%3AVar"  ))

(defrule rule120 (declare (salience 10))
(TripleTemplate (subject  ?slotitems ) (predicate  <http://clips.script/constraints> ) (object  ?listconstraints ))
(TripleTemplate (subject  ?slotitems ) (predicate  <http://white.gobo/local/b/nfc895320_n4339#add-args-as-constraints-from> ) (object  ?itemlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#numeric-greater-than> (<http://www.w3.org/2007/rif-builtin-function#count> ?itemlist  )  "0^^http://www.w3.org/2001/XMLSchema#integer"  ))

(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?itemlist  ))

(TripleTemplate (subject  = (<http://www.w3.org/2007/rif-builtin-function#get> ?itemlist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )) (predicate  <http://example.com/as-constraint> ) (object  ?clipsconstraint ))
	=>
 (do-for-all-facts (( ?fct45 TripleTemplate)) (and (eq ?fct45:subject   ?slotitems  )  (eq ?fct45:predicate   <http://clips.script/constraints>  ) ) (retract ?fct45  ) ) (assert(TripleTemplate (subject  ?slotitems ) (predicate  <http://clips.script/constraints> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?listconstraints   ?clipsconstraint  )))) (do-for-all-facts (( ?fct44 TripleTemplate)) (and (eq ?fct44:subject   ?slotitems  )  (eq ?fct44:predicate   <http://white.gobo/local/b/nfc895320_n4339#add-args-as-constraints-from>  ) ) (retract ?fct44  ) ) (assert(TripleTemplate (subject  ?slotitems ) (predicate  <http://white.gobo/local/b/nfc895320_n4339#add-args-as-constraints-from> ) (object  (<http://www.w3.org/2007/rif-builtin-function#remove> ?itemlist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )))))

(defrule rule121 (declare (salience 10))
(Member (class  <http://white.gobo/modelA#ExpressionGenerator> ) (instance  ?riflist ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://www.w3.org/2007/rif#items> ) (object  ?itemlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?itemlist  ))

(not
(exists
(TripleTemplate (subject  ?riflist ) (predicate  <http://www.w3.org/2007/rif#rest> ) (object  ?rest ))
)
)
	=>
 (bind ?function   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/as-expression> ) (object  ?function )))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-name> ) (object  "%3Chttp%3A%2F%2Fwww.w3.org%2F2007%2Frif-builtin-function%23make-list%3E" )))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>))))(assert(TripleTemplate (subject  ?function ) (predicate  <http://white.gobo/local/b/nfc895320_n4339#add-args-as-expression-from> ) (object  ?itemlist ))))

(defrule rule122 (declare (salience 10))
(TripleTemplate (subject  ?function ) (predicate  <http://white.gobo/local/b/nfc895320_n4339#add-args-as-expression-from> ) (object  ?itemlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?itemlist  ))

(test (eq "0^^http://www.w3.org/2001/XMLSchema#integer"   (<http://www.w3.org/2007/rif-builtin-function#count> ?itemlist  ) ))

	=>
 (retract(assert(TripleTemplate (subject  ?function ) (predicate  <http://white.gobo/local/b/nfc895320_n4339#add-args-as-expression-from> ) (object  ?itemlist ))) ))

(defrule rule123 (declare (salience -101))
(TripleTemplate (subject  ?rif ) (predicate  <http://white.gobo/local/b/nfc895320_n4339#add-args-as-expression-from> ) (object  ?arglist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#numeric-greater-than> (<http://www.w3.org/2007/rif-builtin-function#count> ?arglist  )  "0^^http://www.w3.org/2001/XMLSchema#integer"  ))

	=>
(assert(Member (instance  ?rif ) (class  <http://example.com/couldnt-add-all-items> ))) (<http://white.gobo/set-graph-in-errorstate> "Missing%20items%20for%20list%28ex%3Acouldnt-add-all-items%29"  ))

(defrule rule124 (declare (salience 10))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rest ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://www.w3.org/2007/rif#rest> ) (object  ?rest ))
(TripleTemplate (subject  ?rest ) (predicate  <http://example.com/as-expression> ) (object  ?clipsrestvar ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/add-as-pattern> ) (object  ?defrule ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://white.gobo/modelA#binds-variable> ) (object  ?clipsrestvar ))
(Atom (op  <http://white.gobo/local/b/nfc895320_n4339#combine-multifield-as-list> ) (args  ?rest  ?multifieldvar ))
(not
(TripleTemplate (subject  ?defrule ) (predicate  <http://example.com/bound-variable> ) (object  ?clipsrestvar ))
)
	=>
 (bind ?expand   (<http://white.gobo/new-blanknode>) ) (bind ?function   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?clipsrestvar ) (predicate  <http://clips.script/var-as-const-expr> ) (object  ?function )))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-name> ) (object  "%3Chttp%3A%2F%2Fwww.w3.org%2F2007%2Frif-builtin-function%23make-list%3E" )))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?expand  ))))(assert(TripleTemplate (subject  ?expand ) (predicate  <http://clips.script/function-name> ) (object  "expand%24" )))(assert(TripleTemplate (subject  ?expand ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?multifieldvar  )))))

(defrule rule125 (declare (salience 10))
(TripleTemplate (subject  ?firstarg ) (predicate  <http://example.com/as-expression> ) (object  ?firstasexpression ))
(TripleTemplate (subject  ?function ) (predicate  <http://white.gobo/local/b/nfc895320_n4339#add-args-as-expression-from> ) (object  ?itemlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#numeric-greater-than> (<http://www.w3.org/2007/rif-builtin-function#count> ?itemlist  )  "0^^http://www.w3.org/2001/XMLSchema#integer"  ))

(test (eq ?firstarg   (<http://www.w3.org/2007/rif-builtin-function#get> ?itemlist   "0^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-args> ) (object  ?currentexprlist ))
	=>
 (do-for-all-facts (( ?fct41 TripleTemplate)) (and (eq ?fct41:subject   ?function  )  (eq ?fct41:predicate   <http://clips.script/function-args>  ) ) (retract ?fct41  ) ) (assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?currentexprlist   ?firstasexpression  )))) (do-for-all-facts (( ?fct42 TripleTemplate)) (and (eq ?fct42:subject   ?function  )  (eq ?fct42:predicate   <http://white.gobo/local/b/nfc895320_n4339#add-args-as-expression-from>  ) ) (retract ?fct42  ) ) (assert(TripleTemplate (subject  ?function ) (predicate  <http://white.gobo/local/b/nfc895320_n4339#add-args-as-expression-from> ) (object  (<http://www.w3.org/2007/rif-builtin-function#remove> ?itemlist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )))))

(defrule rule126 (declare (salience 10))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?riflist ))
(Member (class  <http://white.gobo/modelA#ConstraintGenerator> ) (instance  ?riflist ))
	=>
 (bind ?listasvar   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/as-constraint> ) (object  ?listasvar )))(assert(Member (instance  ?listasvar ) (class  <http://clips.script/Variable> )))(assert(Member (instance  ?listasvar ) (class  <http://example.com/Variable> )))(assert(Member (instance  ?riflist ) (class  <http://white.gobo/modelA#ConstraintNeedsAdditionalPatterns> ))))

(defrule rule127 (declare (salience -1))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?riflist ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/as-lhs-pattern> ) (object  ?pattern ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/add-as-pattern> ) (object  ?defrule ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/as-constraint> ) (object  ?listasvar ))
(TripleTemplate (subject  ?defrule ) (predicate  <http://example.com/bound-variable> ) (object  ?listasvar ))
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
 (bind ?assignpattern   (<http://white.gobo/new-blanknode>) ) (bind ?testvarpattern   (<http://white.gobo/new-blanknode>) ) (bind ?tmplistasvar   (<http://white.gobo/new-blanknode>) ) (bind ?oldpatternlist   (do-for-fact (( ?fct6 TripleTemplate)) (and (eq ?fct6:subject   ?defrule  )  (eq ?fct6:predicate   <http://clips.script/conditional-element>  ) ) (fact-slot-value ?fct6   object  ) )  ) (bind ?testvaraction   (<http://white.gobo/new-blanknode>) )(assert(Member (instance  ?tmplistasvar ) (class  <http://clips.script/Variable> )))(assert(Member (instance  ?tmplistasvar ) (class  <http://example.com/Variable> )))(assert(Member (instance  ?testvarpattern ) (class  <http://clips.script/TestCE> )))(assert(TripleTemplate (subject  ?testvarpattern ) (predicate  <http://clips.script/function-call> ) (object  ?testvaraction )))(assert(TripleTemplate (subject  ?testvaraction ) (predicate  <http://clips.script/function-name> ) (object  "eq" )))(assert(TripleTemplate (subject  ?testvaraction ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?listasvar   ?tmplistasvar  ))))(assert(TripleTemplate (subject  ?riflist ) (predicate  <http://example.com/used-as-pattern-in> ) (object  ?defrule )))(assert(Member (instance  ?assignpattern ) (class  <http://clips.script/AssignedPatternCE> )))(assert(TripleTemplate (subject  ?assignpattern ) (predicate  <http://clips.script/pattern-ce> ) (object  ?pattern )))(assert(TripleTemplate (subject  ?assignpattern ) (predicate  <http://clips.script/fact-var-symbol> ) (object  ?tmplistasvar ))) (do-for-all-facts (( ?fct43 TripleTemplate)) (and (eq ?fct43:subject   ?defrule  )  (eq ?fct43:predicate   <http://clips.script/conditional-element>  ) ) (retract ?fct43  ) ) (assert(TripleTemplate (subject  ?defrule ) (predicate  <http://clips.script/conditional-element> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?oldpatternlist   ?assignpattern   ?testvarpattern  ))))(assert(TripleTemplate (subject  ?defrule ) (predicate  <http://example.com/transfer-bound-variables-from> ) (object  ?pattern ))))

(defrule rule128
(Member (class  <http://white.gobo/modelA#AtomPatternGenerator> ) (instance  ?rifatom ))
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?op ))
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?arglist  ))

(TripleTemplate (subject  ?op ) (predicate  <http://example.com/as-constraint> ) (object  ?constraintop ))
	=>
 (bind ?pattern   (<http://white.gobo/new-blanknode>) ) (bind ?slotop   (<http://white.gobo/new-blanknode>) ) (bind ?slotargs   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifatom ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?pattern )))(assert(Member (instance  ?pattern ) (class  <http://clips.script/TemplatePatternCE> )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/deftemplate-name> ) (object  "Atom" )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/slot> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?slotop   ?slotargs  ))))(assert(TripleTemplate (subject  ?slotop ) (predicate  <http://clips.script/slot-name> ) (object  "op" )))(assert(TripleTemplate (subject  ?slotop ) (predicate  <http://clips.script/constraint> ) (object  ?constraintop )))(assert(TripleTemplate (subject  ?slotargs ) (predicate  <http://clips.script/slot-name> ) (object  "args" )))(assert(TripleTemplate (subject  ?slotargs ) (predicate  <http://clips.script/constraints> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>))))(assert(TripleTemplate (subject  ?slotargs ) (predicate  <http://white.gobo/local/b/nfc895320_n4073#add-atom-args-as-constraint> ) (object  ?arglist ))))

(defrule rule129 (declare (salience -101))
(TripleTemplate (subject  ?rif ) (predicate  <http://white.gobo/local/b/nfc895320_n4073#add-atom-args-as-constraint> ) (object  ?arglist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#numeric-greater-than> (<http://www.w3.org/2007/rif-builtin-function#count> ?arglist  )  "0^^http://www.w3.org/2001/XMLSchema#integer"  ))

	=>
(assert(Member (instance  ?rif ) (class  <http://example.com/couldnt-add-all-argument> ))) (<http://white.gobo/set-graph-in-errorstate> "Missing%20argument%20for%20expression%28ex%3Acouldnt-add-all-argument%29"  ))

(defrule rule130 (declare (salience 10))
(TripleTemplate (subject  ?slotargs ) (predicate  <http://white.gobo/local/b/nfc895320_n4073#add-atom-args-as-constraint> ) (object  ?arglist ))
(TripleTemplate (subject  = (<http://www.w3.org/2007/rif-builtin-function#get> ?arglist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )) (predicate  <http://example.com/as-constraint> ) (object  ?clipsexpr ))
	=>
 (bind ?oldconstraints   (do-for-fact (( ?fct8 TripleTemplate)) (and (eq ?fct8:subject   ?slotargs  )  (eq ?fct8:predicate   <http://clips.script/constraints>  ) ) (fact-slot-value ?fct8   object  ) )  ) (do-for-all-facts (( ?fct48 TripleTemplate)) (and (eq ?fct48:subject   ?slotargs  )  (eq ?fct48:predicate   <http://white.gobo/local/b/nfc895320_n4073#add-atom-args-as-constraint>  ) ) (retract ?fct48  ) ) (assert(TripleTemplate (subject  ?slotargs ) (predicate  <http://white.gobo/local/b/nfc895320_n4073#add-atom-args-as-constraint> ) (object  (<http://www.w3.org/2007/rif-builtin-function#remove> ?arglist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )))) (do-for-all-facts (( ?fct47 TripleTemplate)) (and (eq ?fct47:subject   ?slotargs  )  (eq ?fct47:predicate   <http://clips.script/constraints>  ) ) (retract ?fct47  ) ) (assert(TripleTemplate (subject  ?slotargs ) (predicate  <http://clips.script/constraints> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?oldconstraints   ?clipsexpr  )))))

(defrule rule131
(Member (class  <http://white.gobo/modelA#AtomPatternGenerator> ) (instance  ?rifatom ))
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?op ))
(TripleTemplate (subject  ?op ) (predicate  <http://example.com/as-constraint> ) (object  ?constraintop ))
(not
(exists
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
)
)
	=>
 (bind ?slotargs   (<http://white.gobo/new-blanknode>) ) (bind ?slotop   (<http://white.gobo/new-blanknode>) ) (bind ?pattern   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifatom ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?pattern )))(assert(Member (instance  ?pattern ) (class  <http://clips.script/TemplatePatternCE> )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/deftemplate-name> ) (object  "Atom" )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/slot> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?slotop   ?slotargs  ))))(assert(TripleTemplate (subject  ?slotop ) (predicate  <http://clips.script/slot-name> ) (object  "op" )))(assert(TripleTemplate (subject  ?slotop ) (predicate  <http://clips.script/constraint> ) (object  ?constraintop )))(assert(TripleTemplate (subject  ?slotargs ) (predicate  <http://clips.script/slot-name> ) (object  "args" )))(assert(TripleTemplate (subject  ?slotargs ) (predicate  <http://clips.script/constraints> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>)))))

(defrule rule132
(Member (class  <http://white.gobo/modelA#TripleTemplateGenerator> ) (instance  ?slot ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?slotvalue ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?slotkey ))
(TripleTemplate (subject  ?slotvalue ) (predicate  <http://example.com/as-constraint> ) (object  ?constraintobj ))
(TripleTemplate (subject  ?slotkey ) (predicate  <http://example.com/as-constraint> ) (object  ?constraintpred ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?frameobject ))
(TripleTemplate (subject  ?frameobject ) (predicate  <http://example.com/as-constraint> ) (object  ?constraintsubj ))
(not
(TripleTemplate (subject  ?slotkey ) (predicate  <http://www.w3.org/2007/rif#constIRI> ) (object  "http%3A%2F%2Fwww.w3.org%2F1999%2F02%2F22-rdf-syntax-ns%23type^^http://www.w3.org/2001/XMLSchema#anyURI" ))
)
(not
(exists
(TripleTemplate (subject  ?slot ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?x ))
)
)
	=>
 (bind ?slotpred   (<http://white.gobo/new-blanknode>) ) (bind ?slotobj   (<http://white.gobo/new-blanknode>) ) (bind ?slotsubj   (<http://white.gobo/new-blanknode>) ) (bind ?pattern   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?slot ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?pattern )))(assert(Member (instance  ?pattern ) (class  <http://clips.script/TemplatePatternCE> )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/deftemplate-name> ) (object  "TripleTemplate" )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/slot> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?slotsubj   ?slotpred   ?slotobj  ))))(assert(TripleTemplate (subject  ?slotsubj ) (predicate  <http://clips.script/slot-name> ) (object  "subject" )))(assert(TripleTemplate (subject  ?slotsubj ) (predicate  <http://clips.script/constraint> ) (object  ?constraintsubj )))(assert(TripleTemplate (subject  ?slotpred ) (predicate  <http://clips.script/slot-name> ) (object  "predicate" )))(assert(TripleTemplate (subject  ?slotpred ) (predicate  <http://clips.script/constraint> ) (object  ?constraintpred )))(assert(TripleTemplate (subject  ?slotobj ) (predicate  <http://clips.script/slot-name> ) (object  "object" )))(assert(TripleTemplate (subject  ?slotobj ) (predicate  <http://clips.script/constraint> ) (object  ?constraintobj ))))

(defrule rule133
(Member (class  <http://white.gobo/modelA#TripleTemplateGenerator> ) (instance  ?slot ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?slotvalue ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?slotkey ))
(TripleTemplate (subject  ?slotvalue ) (predicate  <http://example.com/as-constraint> ) (object  ?constraintobj ))
(TripleTemplate (subject  ?slotkey ) (predicate  <http://www.w3.org/2007/rif#constIRI> ) (object  "http%3A%2F%2Fwww.w3.org%2F1999%2F02%2F22-rdf-syntax-ns%23type^^http://www.w3.org/2001/XMLSchema#anyURI" ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?frameobject ))
(TripleTemplate (subject  ?frameobject ) (predicate  <http://example.com/as-constraint> ) (object  ?constraintsubj ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

(not
(exists
(TripleTemplate (subject  ?slot ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?x ))
)
)
	=>
 (bind ?slotclass   (<http://white.gobo/new-blanknode>) ) (bind ?slotinstance   (<http://white.gobo/new-blanknode>) ) (bind ?pattern   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?slot ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?pattern )))(assert(Member (instance  ?pattern ) (class  <http://clips.script/TemplatePatternCE> )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/deftemplate-name> ) (object  "Member" )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/slot> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?slotinstance   ?slotclass  ))))(assert(TripleTemplate (subject  ?slotinstance ) (predicate  <http://clips.script/slot-name> ) (object  "instance" )))(assert(TripleTemplate (subject  ?slotinstance ) (predicate  <http://clips.script/constraint> ) (object  ?constraintsubj )))(assert(TripleTemplate (subject  ?slotclass ) (predicate  <http://clips.script/slot-name> ) (object  "class" )))(assert(TripleTemplate (subject  ?slotclass ) (predicate  <http://clips.script/constraint> ) (object  ?constraintobj ))))

(defrule rule134
(Member (class  <http://white.gobo/modelA#MemberPatternGenerator> ) (instance  ?rifmember ))
(TripleTemplate (subject  ?rifmember ) (predicate  <http://www.w3.org/2007/rif#instance> ) (object  ?rifinstance ))
(TripleTemplate (subject  ?rifmember ) (predicate  <http://www.w3.org/2007/rif#class> ) (object  ?rifclass ))
(TripleTemplate (subject  ?rifinstance ) (predicate  <http://example.com/as-constraint> ) (object  ?constraintinstance ))
(TripleTemplate (subject  ?rifclass ) (predicate  <http://example.com/as-constraint> ) (object  ?constraintclass ))
(not
(exists
(TripleTemplate (subject  ?rifmember ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?x ))
)
)
	=>
 (bind ?slotinstance   (<http://white.gobo/new-blanknode>) ) (bind ?pattern   (<http://white.gobo/new-blanknode>) ) (bind ?slotclass   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifmember ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?pattern )))(assert(Member (instance  ?pattern ) (class  <http://clips.script/TemplatePatternCE> )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/deftemplate-name> ) (object  "Member" )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/slot> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?slotclass   ?slotinstance  ))))(assert(TripleTemplate (subject  ?slotclass ) (predicate  <http://clips.script/slot-name> ) (object  "class" )))(assert(TripleTemplate (subject  ?slotclass ) (predicate  <http://clips.script/constraint> ) (object  ?constraintclass )))(assert(TripleTemplate (subject  ?slotinstance ) (predicate  <http://clips.script/slot-name> ) (object  "instance" )))(assert(TripleTemplate (subject  ?slotinstance ) (predicate  <http://clips.script/constraint> ) (object  ?constraintinstance ))))

(defrule rule135 (declare (salience 50))
(TripleTemplate (subject  ?frameobject ) (predicate  <http://example.com/as-constraint> ) (object  ?constraintsubject ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?frameobject ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://example.com/add-as-pattern> ) (object  ?defrule ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?slotlist  ))

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
(TripleTemplate (subject  ?slotvalue ) (predicate  <http://example.com/as-constraint> ) (object  ?constraintobject ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?slotvalue ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?slotkey ))
(TripleTemplate (subject  ?slotkey ) (predicate  <http://www.w3.org/2007/rif#constIRI> ) (object  "http%3A%2F%2Fwww.w3.org%2F1999%2F02%2F22-rdf-syntax-ns%23type^^http://www.w3.org/2001/XMLSchema#anyURI" ))
(not
(TripleTemplate (subject  ?slot ) (predicate  <http://example.com/used-as-pattern-in> ) (object  ?defrule ))
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
 (bind ?pattern   (<http://white.gobo/new-blanknode>) ) (bind ?slotcls   (<http://white.gobo/new-blanknode>) ) (bind ?slotinstance   (<http://white.gobo/new-blanknode>) ) (bind ?oldpatternlist   (do-for-fact (( ?fct9 TripleTemplate)) (and (eq ?fct9:subject   ?defrule  )  (eq ?fct9:predicate   <http://clips.script/conditional-element>  ) ) (fact-slot-value ?fct9   object  ) )  )(assert(TripleTemplate (subject  ?slot ) (predicate  <http://example.com/used-as-pattern-in> ) (object  ?defrule )))(assert(TripleTemplate (subject  ?rifframe ) (predicate  <http://example.com/used-as-pattern-in> ) (object  ?defrule )))(assert(Member (instance  ?pattern ) (class  <http://clips.script/TemplatePatternCE> )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/deftemplate-name> ) (object  "Member" )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/slot> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?slotinstance   ?slotcls  ))))(assert(TripleTemplate (subject  ?slotinstance ) (predicate  <http://clips.script/slot-name> ) (object  "instance" )))(assert(TripleTemplate (subject  ?slotinstance ) (predicate  <http://clips.script/constraint> ) (object  ?constraintsubject )))(assert(TripleTemplate (subject  ?slotcls ) (predicate  <http://clips.script/slot-name> ) (object  "class" )))(assert(TripleTemplate (subject  ?slotcls ) (predicate  <http://clips.script/constraint> ) (object  ?constraintobject ))) (do-for-all-facts (( ?fct49 TripleTemplate)) (and (eq ?fct49:subject   ?defrule  )  (eq ?fct49:predicate   <http://clips.script/conditional-element>  ) ) (retract ?fct49  ) ) (assert(TripleTemplate (subject  ?defrule ) (predicate  <http://clips.script/conditional-element> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?oldpatternlist   ?pattern  ))))(assert(TripleTemplate (subject  ?defrule ) (predicate  <http://example.com/transfer-bound-variables-from> ) (object  ?constraintsubject )))(assert(TripleTemplate (subject  ?defrule ) (predicate  <http://example.com/transfer-bound-variables-from> ) (object  ?constraintobject ))))

(defrule rule136 (declare (salience -1))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?rifexternal ))
(TripleTemplate (subject  ?rifexternal ) (predicate  <http://www.w3.org/2007/rif#content> ) (object  ?rifatom ))
(TripleTemplate (subject  ?rifexternal ) (predicate  <http://example.com/add-as-pattern> ) (object  ?defrule ))
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?rifconstiristring ))
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?arglist  ))

(TripleTemplate (subject  ?rifconstiristring ) (predicate  <http://www.w3.org/2007/rif#constIRI> ) (object  "http%3A%2F%2Fwww.w3.org%2F2007%2Frif-builtin-predicate%23iri-string^^http://www.w3.org/2001/XMLSchema#anyURI" ))
(TripleTemplate (subject  = (<http://www.w3.org/2007/rif-builtin-function#get> ?arglist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )) (predicate  <http://example.com/as-expression> ) (object  ?clipsvar ))
(TripleTemplate (subject  = (<http://www.w3.org/2007/rif-builtin-function#get> ?arglist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )) (predicate  <http://www.w3.org/2007/rif#varname> ) (object  ?varname ))
(TripleTemplate (subject  = (<http://www.w3.org/2007/rif-builtin-function#get> ?arglist   "1^^http://www.w3.org/2001/XMLSchema#integer"  )) (predicate  <http://example.com/as-expression> ) (object  ?clipsexpression ))
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
(not
(TripleTemplate (subject  ?defrule ) (predicate  <http://example.com/bound-variable> ) (object  ?clipsvar ))
)
(not
(TripleTemplate (subject  ?rifexternal ) (predicate  <http://example.com/used-as-pattern-in> ) (object  ?defrule ))
)
(not
(and
(not
(TripleTemplate (subject  ?defrule ) (predicate  <http://example.com/bound-variable> ) (object  ?clipsexpression ))
)
(exists
(TripleTemplate (subject  ?clipsexpression ) (predicate  <http://clips.script/variable-name> ) (object  ?tmp ))
)
)
)
	=>
(assert(TripleTemplate (subject  ?rifexternal ) (predicate  <http://example.com/used-as-pattern-in> ) (object  ?defrule )))(assert(TripleTemplate (subject  ?clipsvar ) (predicate  <http://clips.script/var-as-const-expr> ) (object  ?clipsexpression ))))

(defrule rule137 (declare (salience -100))
(Member (class  <http://www.w3.org/2007/rif#Do> ) (instance  ?rifnode ))
(exists
(and
(TripleTemplate (subject  ?rifnode ) (predicate  <http://www.w3.org/2007/rif#actionVar> ) (object  ?actionvar ))
(not
(Atom (op  <http://white.gobo/local/b/nfc895320_n3091#processed-actionvar> ) (args  ?rifnode  ?actionvar ))
)
)
)
	=>
(assert(Member (instance  ?rifnode ) (class  <http://example.com/missing-actionvar> ))) (<http://white.gobo/set-graph-in-errorstate> "Missing%20binding%20for%20rif%3AactionVar.%28ex%3Amissing-actionvar%29"  ))

(defrule rule138
(Member (class  <http://www.w3.org/2007/rif#New> ) (instance  ?rifnew ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifvar ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-expression> ) (object  ?clipsvar ))
(TripleTemplate (subject  ?rifdo ) (predicate  <http://www.w3.org/2007/rif#actionVar> ) (object  ?actionvar ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?actionvar   ?rifnew  ))

(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?actionvar   ?rifvar  ))

(TripleTemplate (subject  ?rifdo ) (predicate  <http://example.com/out-transform-do> ) (object  ?actionlist ))
(not
(Atom (op  <http://white.gobo/local/b/nfc895320_n3091#processed-actionvar> ) (args  ?rifdo  ?actionvar ))
)
	=>
 (bind ?function   (<http://white.gobo/new-blanknode>) ) (bind ?binding   (<http://white.gobo/new-blanknode>) )(assert(Atom (op  <http://white.gobo/local/b/nfc895320_n3091#processed-actionvar> ) (args  ?rifdo  ?actionvar ))) (do-for-all-facts (( ?fct53 TripleTemplate)) (and (eq ?fct53:subject   ?rifdo  )  (eq ?fct53:predicate   <http://example.com/out-transform-do>  ) ) (retract ?fct53  ) ) (assert(TripleTemplate (subject  ?rifdo ) (predicate  <http://example.com/out-transform-do> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?actionlist   ?function  ))))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-name> ) (object  "bind" )))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?clipsvar   ?binding  ))))(assert(TripleTemplate (subject  ?binding ) (predicate  <http://clips.script/function-name> ) (object  "%3Chttp%3A%2F%2Fwhite.gobo%2Fnew-blanknode%3E" )))(assert(TripleTemplate (subject  ?binding ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>)))))

(defrule rule139 (declare (salience -100))
(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/out-transform-do> ) (object  ?out ))
	=>
(assert(Member (instance  ?rifnode ) (class  <http://example.com/not-completed-actions> ))) (<http://white.gobo/set-graph-in-errorstate> "Actions%20for%20rif%3ADo%20werent%20translated.%28ex%3Anot-completed-actions%29"  ))

(defrule rule140
(TripleTemplate (subject  ?rifnode ) (predicate  <http://www.w3.org/2007/rif#actions> ) (object  ?actionlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?actionlist  ))

	=>
(assert(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/in-transform-do> ) (object  ?actionlist )))(assert(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/out-transform-do> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>)))))

(defrule rule141
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifvar ))
(TripleTemplate (subject  ?rifvar ) (predicate  <http://example.com/as-expression> ) (object  ?clipsvar ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?rifframe ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?object ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?slotlist  ))

(TripleTemplate (subject  ?object ) (predicate  <http://example.com/as-expression> ) (object  ?subj ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?slotvalue ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?slotkey ))
(TripleTemplate (subject  ?slotkey ) (predicate  <http://example.com/as-expression> ) (object  ?pred ))
(TripleTemplate (subject  ?rifdo ) (predicate  <http://www.w3.org/2007/rif#actionVar> ) (object  ?actionvar ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?actionvar   ?rifframe  ))

(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?actionvar   ?rifvar  ))

(TripleTemplate (subject  ?rifdo ) (predicate  <http://example.com/out-transform-do> ) (object  ?actionlist ))
(not
(Atom (op  <http://white.gobo/local/b/nfc895320_n3091#processed-actionvar> ) (args  ?rifdo  ?actionvar ))
)
	=>
 (bind ?factvar   (<http://white.gobo/new-blanknode>) ) (bind ?function   (<http://white.gobo/new-blanknode>) ) (bind ?extractval   (<http://white.gobo/new-blanknode>) ) (bind ?symbolsubject   (<http://white.gobo/new-blanknode>) ) (bind ?funccheckpred   (<http://white.gobo/new-blanknode>) ) (bind ?binding   (<http://white.gobo/new-blanknode>) ) (bind ?query   (<http://white.gobo/new-blanknode>) ) (bind ?slotsubj   (<http://white.gobo/new-blanknode>) ) (bind ?slotpred   (<http://white.gobo/new-blanknode>) ) (bind ?funcchecksubj   (<http://white.gobo/new-blanknode>) ) (bind ?template   (<http://white.gobo/new-blanknode>) )(assert(Atom (op  <http://white.gobo/local/b/nfc895320_n3091#processed-actionvar> ) (args  ?rifdo  ?actionvar ))) (do-for-all-facts (( ?fct50 TripleTemplate)) (and (eq ?fct50:subject   ?rifdo  )  (eq ?fct50:predicate   <http://example.com/out-transform-do>  ) ) (retract ?fct50  ) ) (assert(TripleTemplate (subject  ?rifdo ) (predicate  <http://example.com/out-transform-do> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?actionlist   ?function  ))))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-name> ) (object  "bind" )))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?clipsvar   ?binding  ))))(assert(Member (instance  ?binding ) (class  <http://clips.script/DoForFact> )))(assert(TripleTemplate (subject  ?binding ) (predicate  <http://clips.script/fact-set-template> ) (object  ?template )))(assert(TripleTemplate (subject  ?template ) (predicate  <http://clips.script/deftemplate-name> ) (object  "TripleTemplate" )))(assert(TripleTemplate (subject  ?template ) (predicate  <http://clips.script/fact-set-member-variable> ) (object  ?factvar )))(assert(Member (instance  ?factvar ) (class  <http://clips.script/Variable> )))(assert(Member (instance  ?factvar ) (class  <http://example.com/Variable> )))(assert(TripleTemplate (subject  ?binding ) (predicate  <http://clips.script/query> ) (object  ?query )))(assert(TripleTemplate (subject  ?query ) (predicate  <http://clips.script/function-name> ) (object  "and" )))(assert(TripleTemplate (subject  ?query ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?funcchecksubj   ?funccheckpred  ))))(assert(TripleTemplate (subject  ?slotsubj ) (predicate  <http://clips.script/member-variable> ) (object  ?factvar )))(assert(TripleTemplate (subject  ?slotsubj ) (predicate  <http://clips.script/member-slot-name> ) (object  "subject" )))(assert(TripleTemplate (subject  ?funcchecksubj ) (predicate  <http://clips.script/function-name> ) (object  "eq" )))(assert(TripleTemplate (subject  ?funcchecksubj ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?slotsubj   ?subj  ))))(assert(TripleTemplate (subject  ?slotpred ) (predicate  <http://clips.script/member-variable> ) (object  ?factvar )))(assert(TripleTemplate (subject  ?slotpred ) (predicate  <http://clips.script/member-slot-name> ) (object  "predicate" )))(assert(TripleTemplate (subject  ?funccheckpred ) (predicate  <http://clips.script/function-name> ) (object  "eq" )))(assert(TripleTemplate (subject  ?funccheckpred ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?slotpred   ?pred  ))))(assert(TripleTemplate (subject  ?binding ) (predicate  <http://clips.script/action> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?extractval  ))))(assert(TripleTemplate (subject  ?extractval ) (predicate  <http://clips.script/function-name> ) (object  "fact-slot-value" )))(assert(TripleTemplate (subject  ?extractval ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?factvar   ?symbolsubject  ))))(assert(TripleTemplate (subject  ?symbolsubject ) (predicate  <http://clips.script/symbol> ) (object  "object" ))))

(defrule rule142
(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/out-transform-do> ) (object  ?out ))
(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/in-transform-do> ) (object  ?in ))
(test (eq "0^^http://www.w3.org/2001/XMLSchema#integer"   (<http://www.w3.org/2007/rif-builtin-function#count> ?in  ) ))

	=>
(assert(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/as-action> ) (object  ?out ))) (retract(assert(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/in-transform-do> ) (object  ?in ))) ) (retract(assert(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/out-transform-do> ) (object  ?out ))) ))

(defrule rule143
(Member (class  <http://www.w3.org/2007/rif#Do> ) (instance  ?rifnode ))
(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/out-transform-do> ) (object  ?out ))
(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/in-transform-do> ) (object  ?in ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#numeric-not-equal> "0^^http://www.w3.org/2001/XMLSchema#integer"   (<http://www.w3.org/2007/rif-builtin-function#count> ?in  ) ))

(TripleTemplate (subject  = (<http://www.w3.org/2007/rif-builtin-function#get> ?in   "0^^http://www.w3.org/2001/XMLSchema#integer"  )) (predicate  <http://example.com/as-action> ) (object  ?nextactions ))
(not
(exists
(and
(TripleTemplate (subject  ?rifnode ) (predicate  <http://www.w3.org/2007/rif#actionVar> ) (object  ?actionvar ))
(not
(Atom (op  <http://white.gobo/local/b/nfc895320_n3091#processed-actionvar> ) (args  ?rifnode  ?actionvar ))
)
)
)
)
	=>
 (do-for-all-facts (( ?fct51 TripleTemplate)) (and (eq ?fct51:subject   ?rifnode  )  (eq ?fct51:predicate   <http://example.com/in-transform-do>  ) ) (retract ?fct51  ) ) (assert(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/in-transform-do> ) (object  (<http://www.w3.org/2007/rif-builtin-function#remove> ?in   "0^^http://www.w3.org/2001/XMLSchema#integer"  )))) (do-for-all-facts (( ?fct52 TripleTemplate)) (and (eq ?fct52:subject   ?rifnode  )  (eq ?fct52:predicate   <http://example.com/out-transform-do>  ) ) (retract ?fct52  ) ) (assert(TripleTemplate (subject  ?rifnode ) (predicate  <http://example.com/out-transform-do> ) (object  (<http://www.w3.org/2007/rif-builtin-function#concatenate> ?out   ?nextactions  )))))

(defrule rule144
(or
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?factable ))
(Member (class  <http://www.w3.org/2007/rif#Member> ) (instance  ?factable ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?factable ))
(Member (class  <http://www.w3.org/2007/rif#Subclass> ) (instance  ?factable ))
)
(TripleTemplate (subject  ?factable ) (predicate  <http://example.com/as-rhspattern> ) (object  ?newrhspattern ))
(TripleTemplate (subject  ?group ) (predicate  <http://example.com/combine-deffacts-in> ) (object  ?deffacts ))
(TripleTemplate (subject  ?group ) (predicate  <http://www.w3.org/2007/rif#sentences> ) (object  ?sentences ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?sentences   ?factable  ))

(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?sentences  ))

	=>
 (bind ?rhspatternlist   (do-for-fact (( ?fct10 TripleTemplate)) (and (eq ?fct10:subject   ?deffacts  )  (eq ?fct10:predicate   <http://clips.script/rhs-pattern>  ) ) (fact-slot-value ?fct10   object  ) )  ) (do-for-all-facts (( ?fct54 TripleTemplate)) (and (eq ?fct54:subject   ?deffacts  )  (eq ?fct54:predicate   <http://clips.script/rhs-pattern>  ) ) (retract ?fct54  ) ) (assert(TripleTemplate (subject  ?deffacts ) (predicate  <http://clips.script/rhs-pattern> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?rhspatternlist   ?newrhspattern  )))))

(defrule rule145
(TripleTemplate (subject  ?group ) (predicate  <http://www.w3.org/2007/rif#sentences> ) (object  ?sentences ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?sentences  ))

(exists
(and
(or
(Member (class  <http://www.w3.org/2007/rif#Subclass> ) (instance  ?factable ))
(Member (class  <http://www.w3.org/2007/rif#Member> ) (instance  ?factable ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?factable ))
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?factable ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?sentences   ?factable  ))

)
)
	=>
 (bind ?deffacts   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?group ) (predicate  <http://example.com/combine-deffacts-in> ) (object  ?deffacts )))(assert(Member (instance  ?deffacts ) (class  <http://clips.script/Deffacts> )))(assert(TripleTemplate (subject  ?deffacts ) (predicate  <http://clips.script/rhs-pattern> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>)))))

(defrule rule146
(Member (class  <http://white.gobo/modelA#TestPatternEqualGenerator> ) (instance  ?rifequal ))
(TripleTemplate (subject  ?rifequal ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?rifright ))
(TripleTemplate (subject  ?rifequal ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?rifleft ))
	=>
(assert(Member (instance  ?rifleft ) (class  <http://white.gobo/modelA#ExpressionGenerator> )))(assert(Member (instance  ?rifright ) (class  <http://white.gobo/modelA#ExpressionGenerator> ))))

(defrule rule147
(Member (class  <http://white.gobo/modelA#TestPatternLeftAssignGenerator> ) (instance  ?rifequal ))
(TripleTemplate (subject  ?rifequal ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?rifright ))
(TripleTemplate (subject  ?rifequal ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?rifleft ))
(TripleTemplate (subject  ?rifright ) (predicate  <http://example.com/as-expression> ) (object  ?rightexpr ))
(TripleTemplate (subject  ?rifleft ) (predicate  <http://example.com/as-constraint> ) (object  ?assignvar ))
	=>
(assert(Member (instance  ?assignvar ) (class  <http://white.gobo/modelA#VarAsConstExpr> )))(assert(TripleTemplate (subject  ?assignvar ) (predicate  <http://clips.script/var-as-const-expr> ) (object  ?rightexpr ))))

(defrule rule148
(Member (class  <http://white.gobo/modelA#TestPatternRightAssignGenerator> ) (instance  ?rifequal ))
(TripleTemplate (subject  ?rifequal ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?rifleft ))
	=>
(assert(Member (instance  ?rifleft ) (class  <http://white.gobo/modelA#ExpressionGenerator> ))))

(defrule rule149
(Member (class  <http://white.gobo/modelA#TestPatternRightAssignGenerator> ) (instance  ?rifequal ))
(TripleTemplate (subject  ?rifequal ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?rifleft ))
(TripleTemplate (subject  ?rifequal ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?rifright ))
(TripleTemplate (subject  ?rifleft ) (predicate  <http://example.com/as-expression> ) (object  ?leftexpr ))
(TripleTemplate (subject  ?rifright ) (predicate  <http://example.com/as-expression> ) (object  ?assignvar ))
	=>
(assert(Member (instance  ?assignvar ) (class  <http://white.gobo/modelA#VarAsConstExpr> )))(assert(TripleTemplate (subject  ?assignvar ) (predicate  <http://clips.script/var-as-const-expr> ) (object  ?leftexpr ))))

(defrule rule150
(Member (class  <http://white.gobo/modelA#TestPatternEqualGenerator> ) (instance  ?rifequal ))
(TripleTemplate (subject  ?rifequal ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?rifright ))
(TripleTemplate (subject  ?rifequal ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?rifleft ))
(TripleTemplate (subject  ?rifright ) (predicate  <http://example.com/as-expression> ) (object  ?rightexpr ))
(TripleTemplate (subject  ?rifleft ) (predicate  <http://example.com/as-expression> ) (object  ?leftexpr ))
(not
(exists
(TripleTemplate (subject  ?rifequal ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?x ))
)
)
	=>
 (bind ?pattern   (<http://white.gobo/new-blanknode>) ) (bind ?action   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifequal ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?pattern )))(assert(Member (instance  ?pattern ) (class  <http://clips.script/TestCE> )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/function-call> ) (object  ?action )))(assert(TripleTemplate (subject  ?action ) (predicate  <http://clips.script/function-name> ) (object  "eq" )))(assert(TripleTemplate (subject  ?action ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?leftexpr   ?rightexpr  )))))

(defrule rule151 (declare (salience 100))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?target ))
(TripleTemplate (subject  ?rifnot ) (predicate  <http://white.gobo/local/b/nfc895320_n1769#give-inheritance> ) (object  ?target ))
(or
(Member (class  <http://www.w3.org/2007/rif#Exists> ) (instance  ?rifnot ))
(Member (class  <http://www.w3.org/2007/rif#Or> ) (instance  ?rifnot ))
(Member (class  <http://www.w3.org/2007/rif#INeg> ) (instance  ?rifnot ))
)
	=>
(assert(TripleTemplate (subject  ?rifnot ) (predicate  <http://example.com/inherits-data> ) (object  ?target ))))

(defrule rule152 (declare (salience 100))
(TripleTemplate (subject  ?document ) (predicate  <http://www.w3.org/2007/rif#payload> ) (object  ?group ))
(TripleTemplate (subject  ?group ) (predicate  <http://white.gobo/local/b/nfc895320_n1769#give-inheritance> ) (object  ?localconst ))
	=>
(assert(TripleTemplate (subject  ?document ) (predicate  <http://example.com/inherits-data> ) (object  ?localconst ))))

(defrule rule153 (declare (salience 100))
(or
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#content> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#super> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#instance> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#rest> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#if> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#meta> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#then> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#sub> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#target> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#pattern> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#class> ) (object  ?child ))
)
(TripleTemplate (subject  ?child ) (predicate  <http://white.gobo/local/b/nfc895320_n1769#give-inheritance> ) (object  ?target ))
	=>
(assert(TripleTemplate (subject  ?parent ) (predicate  <http://white.gobo/local/b/nfc895320_n1769#give-inheritance> ) (object  ?target ))))

(defrule rule154 (declare (salience 100))
(or
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?child ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?child ))
)
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?slotlist  ))

(or
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?child ))
(exists
(TripleTemplate (subject  ?child ) (predicate  <http://www.w3.org/2007/rif#constname> ) (object  ?x ))
)
)
	=>
(assert(TripleTemplate (subject  ?parent ) (predicate  <http://white.gobo/local/b/nfc895320_n1769#give-inheritance> ) (object  ?child ))))

(defrule rule155 (declare (salience 100))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?var ))
(Member (class  <http://www.w3.org/2007/rif#New> ) (instance  ?assign ))
(TripleTemplate (subject  ?rifdo ) (predicate  <http://www.w3.org/2007/rif#actionVar> ) (object  ?actionvar ))
(test (eq ?var   (<http://www.w3.org/2007/rif-builtin-function#get> ?actionvar   "0^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

(test (eq ?assign   (<http://www.w3.org/2007/rif-builtin-function#get> ?actionvar   "1^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

	=>
(assert(Member (instance  ?var ) (class  <http://white.gobo/modelA#NewVar> ))))

(defrule rule156 (declare (salience 100))
(Member (class  <http://www.w3.org/2007/rif#Document> ) (instance  ?document ))
(TripleTemplate (subject  ?document ) (predicate  <http://white.gobo/local/b/nfc895320_n1769#give-inheritance> ) (object  ?localconst ))
	=>
(assert(TripleTemplate (subject  ?document ) (predicate  <http://example.com/inherits-data> ) (object  ?localconst ))))

(defrule rule157 (declare (salience 100))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#formula> ) (object  ?child ))
(TripleTemplate (subject  ?child ) (predicate  <http://white.gobo/local/b/nfc895320_n1769#give-inheritance> ) (object  ?target ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#vars> ) (object  ?varlist ))
(TripleTemplate (subject  ?target ) (predicate  <http://www.w3.org/2007/rif#varname> ) (object  ?name ))
(TripleTemplate (subject  ?var ) (predicate  <http://www.w3.org/2007/rif#varname> ) (object  ?name ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?varlist   ?var  ))

	=>
(assert(TripleTemplate (subject  ?var ) (predicate  <http://example.com/inherits-data> ) (object  ?target ))))

(defrule rule158 (declare (salience 100))
(or
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#items> ) (object  ?arglist ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?arglist  ))

(or
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?child ))
(and
(Member (class  <http://www.w3.org/2007/rif#Const> ) (instance  ?child ))
(exists
(TripleTemplate (subject  ?child ) (predicate  <http://www.w3.org/2007/rif#constname> ) (object  ?x ))
)
)
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?arglist   ?child  ))

	=>
(assert(TripleTemplate (subject  ?parent ) (predicate  <http://white.gobo/local/b/nfc895320_n1769#give-inheritance> ) (object  ?child ))))

(defrule rule159 (declare (salience 100))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?rifconstraint ))
(TripleTemplate (subject  ?rifconstraint ) (predicate  <http://white.gobo/local/b/nfc895320_n1769#give-inheritance> ) (object  ?target ))
(or
(Member (class  <http://white.gobo/modelA#ConstraintGenerator> ) (instance  ?rifconstraint ))
(Member (class  <http://white.gobo/modelA#ConditionGenerator> ) (instance  ?rifconstraint ))
)
	=>
(assert(TripleTemplate (subject  ?rifconstraint ) (predicate  <http://example.com/inherits-data> ) (object  ?target ))))

(defrule rule160 (declare (salience 100))
(TripleTemplate (subject  ?child ) (predicate  <http://white.gobo/local/b/nfc895320_n1769#give-inheritance> ) (object  ?target ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#formula> ) (object  ?child ))
(not
(exists
(and
(TripleTemplate (subject  ?var ) (predicate  <http://www.w3.org/2007/rif#varname> ) (object  ?name ))
(TripleTemplate (subject  ?target ) (predicate  <http://www.w3.org/2007/rif#varname> ) (object  ?name ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#vars> ) (object  ?varlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?varlist   ?var  ))

)
)
)
	=>
(assert(TripleTemplate (subject  ?parent ) (predicate  <http://white.gobo/local/b/nfc895320_n1769#give-inheritance> ) (object  ?target ))))

(defrule rule161 (declare (salience 80))
(TripleTemplate (subject  ?child ) (predicate  <http://white.gobo/local/b/nfc895320_n1769#give-inheritance> ) (object  ?target ))
	=>
 (retract(assert(TripleTemplate (subject  ?child ) (predicate  <http://white.gobo/local/b/nfc895320_n1769#give-inheritance> ) (object  ?target ))) ))

(defrule rule162 (declare (salience 100))
(or
(Member (class  <http://www.w3.org/2007/rif#Execute> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Assert> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Retract> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Modify> ) (instance  ?child ))
)
(TripleTemplate (subject  ?child ) (predicate  <http://white.gobo/local/b/nfc895320_n1769#give-inheritance> ) (object  ?target ))
(TripleTemplate (subject  ?rifdo ) (predicate  <http://www.w3.org/2007/rif#actions> ) (object  ?childlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?childlist   ?child  ))

	=>
(assert(TripleTemplate (subject  ?target ) (predicate  <http://white.gobo/local/b/nfc895320_n1769#rifdoinheritance> ) (object  ?rifdo ))))

(defrule rule163 (declare (salience 100))
(or
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?childlist ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#sentences> ) (object  ?childlist ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#formulas> ) (object  ?childlist ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?childlist  ))

(TripleTemplate (subject  ?child ) (predicate  <http://white.gobo/local/b/nfc895320_n1769#give-inheritance> ) (object  ?target ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?childlist   ?child  ))

	=>
(assert(TripleTemplate (subject  ?parent ) (predicate  <http://white.gobo/local/b/nfc895320_n1769#give-inheritance> ) (object  ?target ))))

(defrule rule164 (declare (salience 100))
(TripleTemplate (subject  ?var ) (predicate  <http://www.w3.org/2007/rif#varname> ) (object  ?name ))
(TripleTemplate (subject  ?target ) (predicate  <http://www.w3.org/2007/rif#varname> ) (object  ?name ))
(TripleTemplate (subject  ?target ) (predicate  <http://white.gobo/local/b/nfc895320_n1769#rifdoinheritance> ) (object  ?parent ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#actionVar> ) (object  ?actionvar ))
(test (eq ?var   (<http://www.w3.org/2007/rif-builtin-function#get> ?actionvar   "0^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

	=>
(assert(TripleTemplate (subject  ?var ) (predicate  <http://example.com/inherits-data> ) (object  ?target ))))

(defrule rule165 (declare (salience 100))
(or
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?child ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?child ))
)
(TripleTemplate (subject  ?child ) (predicate  <http://white.gobo/local/b/nfc895320_n1769#give-inheritance> ) (object  ?target ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?slotlist  ))

	=>
(assert(TripleTemplate (subject  ?parent ) (predicate  <http://white.gobo/local/b/nfc895320_n1769#give-inheritance> ) (object  ?target ))))

(defrule rule166 (declare (salience 100))
(or
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#rest> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#instance> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#class> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#sub> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#target> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#super> ) (object  ?child ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?child ))
)
(or
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?child ))
(exists
(TripleTemplate (subject  ?child ) (predicate  <http://www.w3.org/2007/rif#constname> ) (object  ?x ))
)
)
	=>
(assert(TripleTemplate (subject  ?parent ) (predicate  <http://white.gobo/local/b/nfc895320_n1769#give-inheritance> ) (object  ?child ))))

(defrule rule167 (declare (salience 100))
(Member (class  <http://white.gobo/modelA#ConditionGenerator> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?target ))
(TripleTemplate (subject  ?term ) (predicate  <http://white.gobo/local/b/nfc895320_n1769#give-inheritance> ) (object  ?target ))
(or
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?term ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?term ))
)
	=>
(assert(TripleTemplate (subject  ?term ) (predicate  <http://example.com/inherits-data> ) (object  ?target ))))

(defrule rule168 (declare (salience 100))
(TripleTemplate (subject  ?child ) (predicate  <http://white.gobo/local/b/nfc895320_n1769#give-inheritance> ) (object  ?target ))
(TripleTemplate (subject  ?rifdo ) (predicate  <http://www.w3.org/2007/rif#actionVar> ) (object  ?actionvar ))
(test (eq ?child   (<http://www.w3.org/2007/rif-builtin-function#get> ?actionvar   "1^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

	=>
(assert(TripleTemplate (subject  ?target ) (predicate  <http://white.gobo/local/b/nfc895320_n1769#rifdoinheritance> ) (object  ?rifdo ))))

(defrule rule169 (declare (salience 100))
(TripleTemplate (subject  ?target ) (predicate  <http://white.gobo/local/b/nfc895320_n1769#rifdoinheritance> ) (object  ?parent ))
(not
(exists
(and
(TripleTemplate (subject  ?target ) (predicate  <http://www.w3.org/2007/rif#varname> ) (object  ?name ))
(TripleTemplate (subject  ?parent ) (predicate  <http://www.w3.org/2007/rif#actionVar> ) (object  ?actionvar ))
(TripleTemplate (subject  ?var ) (predicate  <http://www.w3.org/2007/rif#varname> ) (object  ?name ))
(test (eq ?var   (<http://www.w3.org/2007/rif-builtin-function#get> ?actionvar   "0^^http://www.w3.org/2001/XMLSchema#integer"  ) ))

)
)
)
	=>
(assert(TripleTemplate (subject  ?parent ) (predicate  <http://white.gobo/local/b/nfc895320_n1769#give-inheritance> ) (object  ?target ))))

(defrule rule170 (declare (salience 100))
(Member (class  <http://white.gobo/modelA#PatternGenerator> ) (instance  ?rifformula ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://white.gobo/modelA#pattern-uses-constraint> ) (object  ?superlist ))
(TripleTemplate (subject  ?superlist ) (predicate  <http://www.w3.org/2007/rif#items> ) (object  ?itemlist ))
(or
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Variable> ) (instance  ?child ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?itemlist   ?child  ))

	=>
(assert(Member (instance  ?child ) (class  <http://white.gobo/modelA#ConstraintGenerator> )))(assert(TripleTemplate (subject  ?rifformula ) (predicate  <http://white.gobo/modelA#pattern-uses-constraint> ) (object  ?child ))))

(defrule rule171 (declare (salience 100))
(Member (class  <http://www.w3.org/2007/rif#Slot> ) (instance  ?slot ))
(Member (class  <http://white.gobo/modelA#RHSPatternGenerator> ) (instance  ?rifframe ))
(TripleTemplate (subject  ?rifframe ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

	=>
(assert(Member (instance  ?slot ) (class  <http://white.gobo/modelA#RHSPatternGenerator> ))))

(defrule rule172 (declare (salience 100))
(Member (class  <http://white.gobo/modelA#PatternGenerator> ) (instance  ?rifformula ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
(or
(Member (class  <http://www.w3.org/2007/rif#Variable> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?child ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?arglist   ?child  ))

	=>
(assert(Member (instance  ?child ) (class  <http://white.gobo/modelA#ConstraintGenerator> )))(assert(TripleTemplate (subject  ?rifformula ) (predicate  <http://white.gobo/modelA#pattern-uses-constraint> ) (object  ?child ))))

(defrule rule173 (declare (salience 100))
(or
(Member (class  <http://www.w3.org/2007/rif#Member> ) (instance  ?assert ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?assert ))
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?assert ))
)
(TripleTemplate (subject  ?clause ) (predicate  <http://www.w3.org/2007/rif#then> ) (object  ?assert ))
	=>
(assert(Member (instance  ?assert ) (class  <http://white.gobo/modelA#RHSPatternGenerator> ))))

(defrule rule174 (declare (salience 100))
(Member (class  <http://white.gobo/modelA#ConditionGenerator> ) (instance  ?rifformula ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(Member (class  <http://www.w3.org/2007/rif#Slot> ) (instance  ?slot ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

	=>
(assert(Member (instance  ?slot ) (class  <http://white.gobo/modelA#ConditionGenerator> ))))

(defrule rule175 (declare (salience 100))
(or
(Member (class  <http://www.w3.org/2007/rif#Retract> ) (instance  ?action ))
(Member (class  <http://www.w3.org/2007/rif#Modify> ) (instance  ?action ))
(Member (class  <http://www.w3.org/2007/rif#Assert> ) (instance  ?action ))
)
(TripleTemplate (subject  ?action ) (predicate  <http://www.w3.org/2007/rif#target> ) (object  ?target ))
	=>
(assert(Member (instance  ?target ) (class  <http://white.gobo/modelA#RHSPatternGenerator> ))))

(defrule rule176 (declare (salience 100))
(TripleTemplate (subject  ?rifimply ) (predicate  <http://www.w3.org/2007/rif#then> ) (object  ?action ))
	=>
(assert(Member (instance  ?action ) (class  <http://white.gobo/modelA#ActionGenerator> ))))

(defrule rule177 (declare (salience 100))
(Member (class  <http://white.gobo/modelA#AtomPatternGenerator> ) (instance  ?rifformula ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?child ))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?child ))
	=>
(assert(Member (instance  ?rifformula ) (class  <http://white.gobo/modelA#MultiPatternGenerator> ))))

(defrule rule178 (declare (salience 100))
(Member (class  <http://white.gobo/modelA#ConditionGenerator> ) (instance  ?formula ))
(TripleTemplate (subject  ?formula ) (predicate  <http://www.w3.org/2007/rif#formula> ) (object  ?child ))
	=>
(assert(Member (instance  ?child ) (class  <http://white.gobo/modelA#ConditionGenerator> ))))

(defrule rule179 (declare (salience 100))
(or
(Member (class  <http://www.w3.org/2007/rif#Assert> ) (instance  ?action ))
(Member (class  <http://www.w3.org/2007/rif#Do> ) (instance  ?action ))
(Member (class  <http://www.w3.org/2007/rif#Retract> ) (instance  ?action ))
(Member (class  <http://www.w3.org/2007/rif#Modify> ) (instance  ?action ))
(Member (class  <http://www.w3.org/2007/rif#Execute> ) (instance  ?action ))
)
	=>
(assert(Member (instance  ?action ) (class  <http://white.gobo/modelA#ActionGenerator> ))))

(defrule rule180 (declare (salience 100))
(Member (class  <http://white.gobo/modelA#RHSPatternGenerator> ) (instance  ?patterngen ))
(TripleTemplate (subject  ?patterngen ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
(or
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?term ))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?term ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?arglist   ?term  ))

	=>
(assert(Member (instance  ?term ) (class  <http://white.gobo/modelA#ExpressionGenerator> ))))

(defrule rule181 (declare (salience 100))
(Member (class  <http://white.gobo/modelA#ExpressionGenerator> ) (instance  ?rifexternal ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?rifexternal ))
(TripleTemplate (subject  ?rifexternal ) (predicate  <http://www.w3.org/2007/rif#content> ) (object  ?rifatom ))
(TripleTemplate (subject  ?rifatom ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
(or
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?child ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?arglist   ?child  ))

	=>
(assert(Member (instance  ?child ) (class  <http://white.gobo/modelA#ExpressionGenerator> ))))

(defrule rule182 (declare (salience 100))
(or
(TripleTemplate (subject  ?rifimply ) (predicate  <http://www.w3.org/2007/rif#if> ) (object  ?formula ))
(TripleTemplate (subject  ?rifimply ) (predicate  <http://www.w3.org/2007/rif#pattern> ) (object  ?formula ))
)
	=>
(assert(Member (instance  ?formula ) (class  <http://white.gobo/modelA#ConditionGenerator> ))))

(defrule rule183 (declare (salience 100))
(Member (class  <http://white.gobo/modelA#ConditionGenerator> ) (instance  ?formula ))
(TripleTemplate (subject  ?formula ) (predicate  <http://www.w3.org/2007/rif#formulas> ) (object  ?formulalist ))
(or
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Exists> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#INeg> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#SubClass> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Or> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Equal> ) (instance  ?child ))
(Member (class  <http://www.w3.org/2007/rif#Member> ) (instance  ?child ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?formulalist   ?child  ))

	=>
(assert(Member (instance  ?child ) (class  <http://white.gobo/modelA#ConditionGenerator> ))))

(defrule rule184 (declare (salience 100))
(or
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?rifclause ))
(Member (class  <http://www.w3.org/2007/rif#Member> ) (instance  ?rifclause ))
(Member (class  <http://www.w3.org/2007/rif#Subclass> ) (instance  ?rifclause ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?rifclause ))
)
(TripleTemplate (subject  ?group ) (predicate  <http://www.w3.org/2007/rif#sentences> ) (object  ?sentences ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?sentences  ))

(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?sentences   ?rifclause  ))

	=>
(assert(Member (instance  ?rifclause ) (class  <http://white.gobo/modelA#RHSPatternGenerator> ))))

(defrule rule185 (declare (salience 100))
(or
(Member (class  <http://www.w3.org/2007/rif#Implies> ) (instance  ?rifrule ))
(Member (class  <http://www.w3.org/2007/rif#Forall> ) (instance  ?rifrule ))
)
(TripleTemplate (subject  ?group ) (predicate  <http://www.w3.org/2007/rif#sentences> ) (object  ?sentences ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?sentences  ))

(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?sentences   ?rifrule  ))

	=>
(assert(Member (instance  ?rifrule ) (class  <http://white.gobo/modelA#RuleGenerator> ))))

(defrule rule186 (declare (salience 100))
(or
(Member (class  <http://www.w3.org/2007/rif#Equal> ) (instance  ?rifclause ))
)
(TripleTemplate (subject  ?group ) (predicate  <http://www.w3.org/2007/rif#sentences> ) (object  ?sentences ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?sentences   ?rifclause  ))

(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?sentences  ))

	=>
(assert(Member (instance  ?rifclause ) (class  <http://example.com/equal-not-implemented-as-clause> ))) (<http://white.gobo/set-graph-in-errorstate> "modelA%20cant%20process%20rif%3AEqual%20as%20clause%28ex%3Aequal-not-implemented-as-clause%29"  ))

(defrule rule187 (declare (salience 100))
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?rifand ))
(Member (class  <http://white.gobo/modelA#ActionGenerator> ) (instance  ?rifand ))
(TripleTemplate (subject  ?rifand ) (predicate  <http://www.w3.org/2007/rif#formulas> ) (object  ?actionlist ))
(or
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?subaction ))
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?subaction ))
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?subaction ))
(Member (class  <http://www.w3.org/2007/rif#Subclass> ) (instance  ?subaction ))
(Member (class  <http://www.w3.org/2007/rif#Member> ) (instance  ?subaction ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?actionlist   ?subaction  ))

	=>
(assert(Member (instance  ?subaction ) (class  <http://white.gobo/modelA#ActionGenerator> ))))

(defrule rule188 (declare (salience 100))
(Member (class  <http://white.gobo/modelA#AtomPatternGenerator> ) (instance  ?rifformula ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?arglist ))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?child ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?arglist   ?child  ))

	=>
(assert(Member (instance  ?rifformula ) (class  <http://white.gobo/modelA#MultiPatternGenerator> ))))

(defrule rule189 (declare (salience 100))
(Member (class  <http://white.gobo/modelA#PatternGenerator> ) (instance  ?rifformula ))
(or
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#instance> ) (object  ?child ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?child ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?child ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?child ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?child ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?child ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#class> ) (object  ?child ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#super> ) (object  ?child ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?child ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#sub> ) (object  ?child ))
)
	=>
(assert(Member (instance  ?child ) (class  <http://white.gobo/modelA#ConstraintGenerator> )))(assert(TripleTemplate (subject  ?rifformula ) (predicate  <http://white.gobo/modelA#pattern-uses-constraint> ) (object  ?child ))))

(defrule rule190 (declare (salience 100))
(Member (class  <http://white.gobo/modelA#ExpressionGenerator> ) (instance  ?riflist ))
(TripleTemplate (subject  ?riflist ) (predicate  <http://www.w3.org/2007/rif#items> ) (object  ?arglist ))
(or
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?term ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?term ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?arglist   ?term  ))

	=>
(assert(Member (instance  ?term ) (class  <http://white.gobo/modelA#ExpressionGenerator> ))))

(defrule rule191 (declare (salience 100))
(Member (class  <http://white.gobo/modelA#RHSPatternGenerator> ) (instance  ?patterngen ))
(or
(TripleTemplate (subject  ?patterngen ) (predicate  <http://www.w3.org/2007/rif#instance> ) (object  ?term ))
(TripleTemplate (subject  ?patterngen ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?term ))
(TripleTemplate (subject  ?patterngen ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?term ))
(TripleTemplate (subject  ?patterngen ) (predicate  <http://www.w3.org/2007/rif#super> ) (object  ?term ))
(TripleTemplate (subject  ?patterngen ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?term ))
(TripleTemplate (subject  ?patterngen ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?term ))
(TripleTemplate (subject  ?patterngen ) (predicate  <http://www.w3.org/2007/rif#class> ) (object  ?term ))
(TripleTemplate (subject  ?patterngen ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?term ))
(TripleTemplate (subject  ?patterngen ) (predicate  <http://www.w3.org/2007/rif#sub> ) (object  ?term ))
(TripleTemplate (subject  ?patterngen ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?term ))
)
	=>
(assert(Member (instance  ?term ) (class  <http://white.gobo/modelA#ExpressionGenerator> ))))

(defrule rule192 (declare (salience 100))
(Member (class  <http://www.w3.org/2007/rif#Slot> ) (instance  ?slot ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?child ))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?child ))
(Member (class  <http://white.gobo/modelA#TripleTemplateGenerator> ) (instance  ?rifformula ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

	=>
(assert(Member (instance  ?slot ) (class  <http://white.gobo/modelA#MultiPatternGenerator> ))))

(defrule rule193 (declare (salience 100))
(Member (class  <http://www.w3.org/2007/rif#Forall> ) (instance  ?rifforall ))
(TripleTemplate (subject  ?rifforall ) (predicate  <http://www.w3.org/2007/rif#formula> ) (object  ?action ))
(or
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?action ))
(Member (class  <http://www.w3.org/2007/rif#Subclass> ) (instance  ?action ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?action ))
(Member (class  <http://www.w3.org/2007/rif#Member> ) (instance  ?action ))
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?action ))
)
	=>
(assert(Member (instance  ?action ) (class  <http://white.gobo/modelA#ActionGenerator> ))))

(defrule rule194 (declare (salience 100))
(Member (class  <http://white.gobo/modelA#ConditionGenerator> ) (instance  ?rifformula ))
(or
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?rifformula ))
)
	=>
(assert(Member (instance  ?rifformula ) (class  <http://white.gobo/modelA#PatternGenerator> ))))

(defrule rule195 (declare (salience 10))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?rifexternal ))
(TripleTemplate (subject  ?rifexternal ) (predicate  <http://www.w3.org/2007/rif#content> ) (object  ?content ))
(TripleTemplate (subject  ?content ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?rifop ))
(TripleTemplate (subject  ?content ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?rifarglist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?rifarglist  ))

(TripleTemplate (subject  ?rifop ) (predicate  <http://example.com/as-expression> ) (object  ?functionsymbol ))
(TripleTemplate (subject  ?functionsymbol ) (predicate  <http://clips.script/symbol> ) (object  ?functionname ))
	=>
 (bind ?function   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifexternal ) (predicate  <http://example.com/as-action> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list> ?function  ))))(assert(TripleTemplate (subject  ?rifexternal ) (predicate  <http://example.com/as-expression> ) (object  ?function )))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-name> ) (object  ?functionname )))(assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#make-list>))))(assert(TripleTemplate (subject  ?function ) (predicate  <http://example.com/add-args-from> ) (object  ?rifarglist ))))

(defrule rule196 (declare (salience -50))
(TripleTemplate (subject  ?function ) (predicate  <http://example.com/add-args-from> ) (object  ?rifarglist ))
(not
(test (eq "0^^http://www.w3.org/2001/XMLSchema#integer"   (<http://www.w3.org/2007/rif-builtin-function#count> ?rifarglist  ) ))

)
	=>
(assert(Member (instance  ?function ) (class  <http://example.com/didnt-translate-all-args> ))) (<http://white.gobo/set-graph-in-errorstate> "Didnt%20translate%20all%20arguments%20for%20function%28ex%3Adidnt-translate-all-args%29"  ))

(defrule rule197
(Member (class  <http://white.gobo/modelA#TestPatternExternalGenerator> ) (instance  ?rifexternal ))
	=>
(assert(Member (instance  ?rifexternal ) (class  <http://white.gobo/modelA#ExpressionGenerator> ))))

(defrule rule198
(Member (class  <http://white.gobo/modelA#TestPatternExternalGenerator> ) (instance  ?rifexternal ))
(TripleTemplate (subject  ?rifexternal ) (predicate  <http://example.com/as-expression> ) (object  ?action ))
	=>
 (bind ?pattern   (<http://white.gobo/new-blanknode>) )(assert(TripleTemplate (subject  ?rifexternal ) (predicate  <http://white.gobo/modelA#as-lhs-pattern> ) (object  ?pattern )))(assert(Member (instance  ?pattern ) (class  <http://clips.script/TestCE> )))(assert(TripleTemplate (subject  ?pattern ) (predicate  <http://clips.script/function-call> ) (object  ?action ))))

(defrule rule199 (declare (salience 15))
(TripleTemplate (subject  ?function ) (predicate  <http://example.com/add-args-from> ) (object  ?rifarglist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?rifarglist  ))

(TripleTemplate (subject  = (<http://www.w3.org/2007/rif-builtin-function#get> ?rifarglist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )) (predicate  <http://example.com/as-expression> ) (object  ?clipsexpression ))
	=>
 (bind ?functionargs   (do-for-fact (( ?fct1 TripleTemplate)) (and (eq ?fct1:subject   ?function  )  (eq ?fct1:predicate   <http://clips.script/function-args>  ) ) (fact-slot-value ?fct1   object  ) )  ) (do-for-all-facts (( ?fct56 TripleTemplate)) (and (eq ?fct56:subject   ?function  )  (eq ?fct56:predicate   <http://clips.script/function-args>  ) ) (retract ?fct56  ) ) (assert(TripleTemplate (subject  ?function ) (predicate  <http://clips.script/function-args> ) (object  (<http://www.w3.org/2007/rif-builtin-function#append> ?functionargs   ?clipsexpression  )))) (do-for-all-facts (( ?fct55 TripleTemplate)) (and (eq ?fct55:subject   ?function  )  (eq ?fct55:predicate   <http://example.com/add-args-from>  ) ) (retract ?fct55  ) ) (assert(TripleTemplate (subject  ?function ) (predicate  <http://example.com/add-args-from> ) (object  (<http://www.w3.org/2007/rif-builtin-function#remove> ?rifarglist   "0^^http://www.w3.org/2001/XMLSchema#integer"  )))))

(defrule rule200 (declare (salience 10))
(or
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#right> ) (object  ?rifterm ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#op> ) (object  ?rifterm ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#left> ) (object  ?rifterm ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#object> ) (object  ?rifterm ))
)
(TripleTemplate (subject  ?rifformula ) (predicate  <http://example.com/add-as-pattern> ) (object  ?defrule ))
	=>
(assert(Member (instance  ?rifterm ) (class  <http://example.com/ConstraintGenerator> ))))

(defrule rule201 (declare (salience 10))
(or
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?rifformula ))
)
(TripleTemplate (subject  ?rifparent ) (predicate  <http://www.w3.org/2007/rif#sentences> ) (object  ?sentencelist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?sentencelist   ?rifformula  ))

	=>
(assert(Member (instance  ?rifformula ) (class  <http://white.gobo/modelA#RHSPatternGenerator> ))))

(defrule rule202 (declare (salience 10))
(Member (class  <http://www.w3.org/2007/rif#Implies> ) (instance  ?rifclause ))
(TripleTemplate (subject  ?rifrule ) (predicate  <http://www.w3.org/2007/rif#then> ) (object  ?rifclause ))
(TripleTemplate (subject  ?rifrule ) (predicate  <http://example.com/add-rule-info> ) (object  ?defrule ))
	=>
(assert(TripleTemplate (subject  ?rifclause ) (predicate  <http://example.com/add-rule-info> ) (object  ?defrule ))))

(defrule rule203 (declare (salience 10))
(Member (class  <http://clips.script/Defrule> ) (instance  ?defrule ))
(Atom (op  <http://example.com/currentdefruleindex> ) (args  ?defruleindex ))
(not
(exists
(and
(TripleTemplate (subject  ?x ) (predicate  <http://clips.script/rule-name> ) (object  ?y ))
(test (eq ?y   (<http://www.w3.org/2007/rif-builtin-function#concat> "rule"   ?defruleindex  ) ))

)
)
)
(not
(exists
(TripleTemplate (subject  ?defrule ) (predicate  <http://clips.script/rule-name> ) (object  ?defrulename ))
)
)
	=>
 (retract(assert(Atom (op  <http://example.com/currentdefruleindex> ) (args  ?defruleindex ))) )(assert(Atom (op  <http://example.com/currentdefruleindex> ) (args  (<http://www.w3.org/2007/rif-builtin-function#numeric-add> ?defruleindex   "1^^http://www.w3.org/2001/XMLSchema#integer"  ))))(assert(TripleTemplate (subject  ?defrule ) (predicate  <http://clips.script/rule-name> ) (object  (<http://www.w3.org/2007/rif-builtin-function#concat> "rule"   ?defruleindex  )))))

(defrule rule204 (declare (salience 10))
(TripleTemplate (subject  ?rifdocument ) (predicate  <http://www.w3.org/2007/rif#payload> ) (object  ?rifgroup ))
(not
(exists
(and
(TripleTemplate (subject  ?rifgroup ) (predicate  <http://www.w3.org/2007/rif#behavior> ) (object  ?behavior ))
(TripleTemplate (subject  ?behavior ) (predicate  <http://www.w3.org/2007/rif#Priority> ) (object  ?x ))
)
)
)
	=>
(assert(TripleTemplate (subject  ?rifgroup ) (predicate  <http://white.gobo/local/b/nfc895320_n683#priority> ) (object  "0^^http://www.w3.org/2001/XMLSchema#integer" ))))

(defrule rule205 (declare (salience 10))
(or
(TripleTemplate (subject  ?rifrule ) (predicate  <http://www.w3.org/2007/rif#then> ) (object  ?rifaction ))
(and
(Member (class  <http://www.w3.org/2007/rif#Forall> ) (instance  ?rifrule ))
(TripleTemplate (subject  ?rifrule ) (predicate  <http://www.w3.org/2007/rif#formula> ) (object  ?rifaction ))
)
)
	=>
(assert(TripleTemplate (subject  ?rifrule ) (predicate  <http://white.gobo/local/b/nfc895320_n683#add-as-action> ) (object  ?rifaction ))))

(defrule rule206 (declare (salience 10))
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?rifcondition ))
(TripleTemplate (subject  ?rifcondition ) (predicate  <http://example.com/add-as-pattern> ) (object  ?defrule ))
(Member (class  <http://clips.script/Defrule> ) (instance  ?defrule ))
(TripleTemplate (subject  ?rifcondition ) (predicate  <http://www.w3.org/2007/rif#formulas> ) (object  ?formulalist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#is-list> ?formulalist  ))

(or
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#SubClass> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#Exists> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#Or> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#And> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#Equal> ) (instance  ?formula ))
(Member (class  <http://www.w3.org/2007/rif#INeg> ) (instance  ?formula ))
)
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?formulalist   ?formula  ))

	=>
(assert(TripleTemplate (subject  ?formula ) (predicate  <http://example.com/add-as-pattern> ) (object  ?defrule )))(assert(TripleTemplate (subject  ?rifcondition ) (predicate  <http://example.com/used-as-pattern-in> ) (object  ?defrule ))))

(defrule rule207 (declare (salience 10))
(or
(Member (class  <http://www.w3.org/2007/rif#Forall> ) (instance  ?rifclause ))
(Member (class  <http://www.w3.org/2007/rif#Implies> ) (instance  ?rifclause ))
)
(TripleTemplate (subject  ?rifrule ) (predicate  <http://www.w3.org/2007/rif#formula> ) (object  ?rifclause ))
(TripleTemplate (subject  ?rifrule ) (predicate  <http://example.com/add-rule-info> ) (object  ?defrule ))
	=>
(assert(TripleTemplate (subject  ?rifclause ) (predicate  <http://example.com/add-rule-info> ) (object  ?defrule ))))

(defrule rule208 (declare (salience 10))
(or
(Member (class  <http://www.w3.org/2007/rif#Implies> ) (instance  ?rifrule ))
(Member (class  <http://www.w3.org/2007/rif#Forall> ) (instance  ?rifrule ))
)
(TripleTemplate (subject  ?rifrule ) (predicate  <http://white.gobo/modelA#as-defrule> ) (object  ?clipsrule ))
(TripleTemplate (subject  ?rifgroup ) (predicate  <http://www.w3.org/2007/rif#sentences> ) (object  ?sentences ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?sentences   ?rifrule  ))

(TripleTemplate (subject  ?rifgroup ) (predicate  <http://white.gobo/local/b/nfc895320_n683#priority> ) (object  ?priority ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#numeric-not-equal> ?priority   "0^^http://www.w3.org/2001/XMLSchema#integer"  ))

	=>
(assert(TripleTemplate (subject  ?clipsrule ) (predicate  <http://clips.script/salience> ) (object  ?priority ))))

(defrule rule209 (declare (salience 10))
(or
(TripleTemplate (subject  ?rifaction ) (predicate  <http://white.gobo/modelA#as-action> ) (object  ?clipsaction ))
(TripleTemplate (subject  ?rifaction ) (predicate  <http://example.com/as-action> ) (object  ?clipsaction ))
)
(TripleTemplate (subject  ?rifrule ) (predicate  <http://white.gobo/local/b/nfc895320_n683#add-as-action> ) (object  ?rifaction ))
(TripleTemplate (subject  ?rifrule ) (predicate  <http://white.gobo/modelA#as-defrule> ) (object  ?defrule ))
	=>
(assert(TripleTemplate (subject  ?defrule ) (predicate  <http://clips.script/action> ) (object  ?clipsaction ))))

(defrule rule210 (declare (salience 10))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://example.com/add-as-pattern> ) (object  ?defrule ))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotkey> ) (object  ?rifterm ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

	=>
(assert(Member (instance  ?rifterm ) (class  <http://example.com/ConstraintGenerator> ))))

(defrule rule211 (declare (salience 10))
(TripleTemplate (subject  ?rifrule ) (predicate  <http://www.w3.org/2007/rif#if> ) (object  ?rifcondition ))
(TripleTemplate (subject  ?rifrule ) (predicate  <http://example.com/add-rule-info> ) (object  ?defrule ))
	=>
(assert(TripleTemplate (subject  ?rifcondition ) (predicate  <http://example.com/add-as-pattern> ) (object  ?defrule ))))

(defrule rule212 (declare (salience 10))
(or
(Member (class  <http://www.w3.org/2007/rif#Frame> ) (instance  ?rifformula ))
(Member (class  <http://www.w3.org/2007/rif#Atom> ) (instance  ?rifformula ))
)
(or
(TripleTemplate (subject  ?rifparent ) (predicate  <http://www.w3.org/2007/rif#then> ) (object  ?rifformula ))
(TripleTemplate (subject  ?rifparent ) (predicate  <http://www.w3.org/2007/rif#target> ) (object  ?rifformula ))
)
	=>
(assert(Member (instance  ?rifformula ) (class  <http://white.gobo/modelA#RHSPatternGenerator> ))))

(defrule rule213 (declare (salience 10))
(Member (class  <http://clips.script/Defrule> ) (instance  ?defrule ))
(TripleTemplate (subject  ?defrule ) (predicate  <http://clips.script/rule-name> ) (object  ?existing ))
(Atom (op  <http://example.com/currentdefruleindex> ) (args  ?defruleindex ))
(test (eq ?existing   (<http://www.w3.org/2007/rif-builtin-function#concat> "rule"   ?defruleindex  ) ))

	=>
 (retract(assert(Atom (op  <http://example.com/currentdefruleindex> ) (args  ?defruleindex ))) )(assert(Atom (op  <http://example.com/currentdefruleindex> ) (args  (<http://www.w3.org/2007/rif-builtin-function#numeric-add> ?defruleindex   "1^^http://www.w3.org/2001/XMLSchema#integer"  )))))

(defrule rule214 (declare (salience 10))
(TripleTemplate (subject  ?rifgroup ) (predicate  <http://www.w3.org/2007/rif#behavior> ) (object  ?behavior ))
(TripleTemplate (subject  ?behavior ) (predicate  <http://www.w3.org/2007/rif#Priority> ) (object  ?priority ))
	=>
(assert(TripleTemplate (subject  ?rifgroup ) (predicate  <http://white.gobo/local/b/nfc895320_n683#priority> ) (object  ?priority ))))

(defrule rule215 (declare (salience 10))
(TripleTemplate (subject  ?slot ) (predicate  <http://www.w3.org/2007/rif#slotvalue> ) (object  ?rifterm ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://example.com/add-as-pattern> ) (object  ?defrule ))
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#slots> ) (object  ?slotlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?slotlist   ?slot  ))

	=>
(assert(Member (instance  ?rifterm ) (class  <http://example.com/ConstraintGenerator> ))))

(defrule rule216 (declare (salience 10))
(or
(Member (class  <http://www.w3.org/2007/rif#External> ) (instance  ?rifterm ))
(Member (class  <http://www.w3.org/2007/rif#List> ) (instance  ?rifterm ))
(Member (class  <http://www.w3.org/2007/rif#Const> ) (instance  ?rifterm ))
(Member (class  <http://www.w3.org/2007/rif#Var> ) (instance  ?rifterm ))
)
(TripleTemplate (subject  ?rifformula ) (predicate  <http://www.w3.org/2007/rif#args> ) (object  ?constraintlist ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?constraintlist   ?rifterm  ))

(TripleTemplate (subject  ?rifformula ) (predicate  <http://example.com/add-as-pattern> ) (object  ?defrule ))
	=>
(assert(Member (instance  ?rifterm ) (class  <http://example.com/ConstraintGenerator> ))))

(defrule rule217 (declare (salience 10))
(Member (class  <http://www.w3.org/2007/rif#Group> ) (instance  ?subgroup ))
(not
(exists
(and
(TripleTemplate (subject  ?subgroup ) (predicate  <http://www.w3.org/2007/rif#behavior> ) (object  ?behavior ))
(TripleTemplate (subject  ?behavior ) (predicate  <http://www.w3.org/2007/rif#Priority> ) (object  ?x ))
)
)
)
(TripleTemplate (subject  ?supergroup ) (predicate  <http://white.gobo/local/b/nfc895320_n683#priority> ) (object  ?priority ))
(TripleTemplate (subject  ?supergroup ) (predicate  <http://www.w3.org/2007/rif#sentences> ) (object  ?sentences ))
(test (<http://www.w3.org/2007/rif-builtin-predicate#list-contains> ?sentences   ?subgroup  ))

	=>
(assert(TripleTemplate (subject  ?subgroup ) (predicate  <http://white.gobo/local/b/nfc895320_n683#priority> ) (object  ?priority ))))

(defrule rule218 (declare (salience 10))
(TripleTemplate (subject  ?super ) (predicate  <http://white.gobo/local/b/nfc895320_n683#add-as-action> ) (object  ?sub ))
(TripleTemplate (subject  ?sub ) (predicate  <http://white.gobo/local/b/nfc895320_n683#add-as-action> ) (object  ?rifaction ))
	=>
(assert(TripleTemplate (subject  ?super ) (predicate  <http://white.gobo/local/b/nfc895320_n683#add-as-action> ) (object  ?rifaction ))))

(deffacts facts643460e0
(Atom (op  <http://example.com/currentfactindex> ) (args  "1^^http://www.w3.org/2001/XMLSchema#integer" ))
)

(deffacts facts64591100
(Atom (op  <http://example.com/currentdefruleindex> ) (args  "0^^http://www.w3.org/2001/XMLSchema#integer" ))
)

