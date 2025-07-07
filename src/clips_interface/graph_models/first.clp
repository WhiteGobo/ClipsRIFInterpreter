;##dummy definitions done by the system
;(deftemplate TripleTemplate
;        (slot subject)
;        (slot predicate)
;        (slot object)
;        (slot context))
;(deffunction PercentDecoding (?x) (return "dummy"))

;(deftemplate Atom
;	(slot op)
;	(multislot args))

;(defclass AtomList (multislot items))

(defclass ReturnValue (is-a USER))
(defclass PatternTerm (is-a ReturnValue)
	(slot term) (multislot checks)
)
(defclass ActionTerm (is-a ReturnValue)
	(slot term) (multislot assi)
)


;##helper functions
(deffunction append$ (?l $?x) (insert$ ?l (+ 1 (length$ ?l)) $?x))
(deffunction combinelist$ (?lx ?ly) (create$ (expand$ ?lx) (expand$ ?ly)))

(deffunction RDFgetLiteralValue (?x)
	(bind ?pos (str-index "^^" ?x))
	(if ?pos then
		(return (sub-string 0 (- ?pos 1) ?x)))
	(bind ?pos (str-index "@" ?x))
	(if ?pos then
		(return (sub-string 0 (- ?pos 1) ?x)))
	(return ?x)
)

(deffunction RIFConst_ExtractURI (?x)
	(bind ?x1 (RDFgetLiteralValue ?x))
	(sym-cat "<" (PercentDecoding ?x1) ">")
)

;## create clips function
(deffunction printrule (?rulename ?declarations ?lhs ?rhs) (str-cat "
(defrule " ?rulename" " ?declarations "
" ?lhs 
"	=>
" ?rhs "
)"))

(deffunction print-script (?scriptname ?action)
	(str-cat "(deffunction " ?scriptname " ()
	" ?action " )
"))

(deffunction print-bind-new (?varname)
	(str-cat "(bind "?varname" (<http://white.gobo/new-blanknode>))")
)

(deffunction print-and (?conditions)
	(bind ?l (length$ ?conditions))
	(if (= ?l 0) then
		(set-error "no statements found.")
		(return ""))
	(if (= ?l 1)
		then (return (nth$ 1 ?conditions))
		else (return (str-cat "(and " (expand$ ?conditions) ")"))
	)
)

(deffunction print-ifthen (?condition ?action) (str-cat
"	(if " ?condition "
	then
	" ?action "
	)"
))

(deffunction print-anyobjectpattern (?varname) (str-cat
"(TripleTemplate (subject " ?varname "))"
))


(deffunction print-deffacts (?name ?triples) (str-cat
"(deffacts " ?name "
	" ?triples ")
"))

;TODO: accept multislot for args
(deffunction print-atom (?op ?args) (str-cat 
"	(Atom
		(op "?op")
		(args "?args"))"
	))
(deffunction print-action (?op ?args) (str-cat "("?op" "?args")"))

(deffunction print-membercondition (?instance ?class)
	(bind ?tmp (str-cat "?" (gensym)))
	(if (eq ?instance nil) then (bind ?checkinst "")
	else (bind ?checkinst (str-cat "		(eq " ?tmp ":instance " ?instance ")
"
	)))
	(if (eq ?class nil) then (bind ?checkcls "")
	else (bind ?checkcls (str-cat "		(eq " ?tmp ":class " ?class ")
"
	)))
	(str-cat 
"	(neq 0 (length$ (find-fact ((" ?tmp " Member)) (and
"?checkinst ?checkcls"))))"))

(deffunction print-subclasscondition (?sub ?super)
	(bind ?tmp (str-cat "?" (gensym)))
	(if (eq ?sub nil) then (bind ?checksub "")
	else (bind ?checksub (str-cat "		(eq " ?tmp ":sub " ?sub ")
"
	)))
	(if (eq ?super nil) then (bind ?checksuper "")
	else (bind ?checksuper (str-cat "		(eq " ?tmp ":super " ?super ")
"
	)))
	(str-cat 
"	(neq 0 (length$ (find-fact ((" ?tmp " Subclass)) (and
"?checksub ?checksuper"))))"))

(deffunction print-triplecondition (?subject ?predicate ?object)
	(bind ?tmp (str-cat "?" (gensym)))
	(if (eq ?subject nil) then (bind ?checksubj "")
	else (bind ?checksubj (str-cat "		(eq " ?tmp ":subject " ?subject ")
"
	)))
	(if (eq ?predicate nil) then (bind ?checkpred "")
	else (bind ?checkpred (str-cat "		(eq "?tmp":predicate " ?predicate ")
"
	)))
	(if (eq ?object nil) then (bind ?checkobj "")
	else (bind ?checkobj (str-cat "		(eq "?tmp":object " ?object ")"
	)))
	(str-cat 
"	(neq 0 (length$ (find-fact ((" ?tmp " TripleTemplate)) (and
"?checksubj ?checkpred ?checkobj"))))"))

(deffunction print-atomcondition (?op ?args)
	(if (neq MULTIFIELD (type ?args)) then
		(set-error "print atom needs multifield")
		(return ""))
	(if (eq 0 (length$ ?args)) then
		(bind ?argstring "(create$)")
	else
		(bind ?l (create$ "(create$"))
		(foreach ?x ?args
			(bind ?l (append$ ?l (create$ " " ?x))))
		(bind ?l (append$ ?l ")"))
		(bind ?argstring (str-cat (expand$ ?l)))
	)
	(bind ?tmp (str-cat "?" (gensym)))
	(str-cat 
"	(neq 0 (length$ (find-fact ((" ?tmp " Atom)) (and
		(eq " ?tmp ":op " ?op ")
		(eq "?tmp":args " ?argstring ")))))"))

(deffunction print-neg (?x) (str-cat "(not " ?x ")"))
(deffunction print-triple (?subject ?predicate ?object) (str-cat 
"	(TripleTemplate
		(subject " ?subject ")
		(predicate " ?predicate ")
		(object " ?object "))"
	))

(deffunction print-member (?instance ?class) (str-cat 
"	(Member
		(instance " ?instance ")
		(class " ?class "))"
	))

(deffunction print-subclass (?sub ?super) (str-cat 
"	(Subclass
		(sub " ?sub ")
		(super " ?super "))"
	))

(deffunction print-assert (?x) (str-cat 
"	(assert "?x")
"))

(deffunction print-assertTriple (?subject ?predicate ?object) 
	(print-assert (print-triple ?subject ?predicate ?object))
)


(deffunction print-retracttriples (?factcondition) (str-cat
"	(do-for-all-facts ((?fct TripleTemplate)) "?factcondition"
		(retract ?fct))"
))

(deffunction print-retractatoms (?factcondition) (str-cat
"	(do-for-all-facts ((?fct Atom)) "?factcondition"
		(retract ?fct))"
))

(deffunction print-retractsubject (?subject) (str-cat
"	(do-for-all-facts ((?fct TripleTemplate)) (eq ?fct:subject "?subject")
		(retract ?fct))"
))


(deffunction print-retractattribute (?subject ?predicate) (str-cat
"	(do-for-all-facts ((?fct TripleTemplate)) 
		(and 
			(eq ?fct:subject "?subject")
			(eq ?fct:predicate "?predicate"))
		(retract ?fct))"
))

;##thingies ??

(defclass helperfact (is-a USER) (slot s) (slot p) (slot o));helperclass
(defclass VARIABLE (is-a USER)
	(slot varname))

(defmessage-handler SYMBOL var-to-string ()
	(str-cat ?self)
)
(defmessage-handler VARIABLE var-to-string ()
	(str-cat "?" ?self:varname)
)

;##class definitions

; each instance of rif:const represents like a node or so
;rdf:type <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>
;rif:Const <http://www.w3.org/2007/rif#Const>
;rif:constIRI <http://www.w3.org/2007/rif#constIRI>

;#abstract classes
(defclass RDFObj (is-a USER)
	(slot node))

(defclass RDFList (is-a RDFObj)
	(multislot items))

(defclass RIFObj (is-a RDFObj))

(defclass AbsRIFSentence (is-a RIFObj))
(defclass AbsRIFAction (is-a RIFObj))
(defclass AbsRIFPattern (is-a RIFObj))
(defclass AbsRIFCondition (is-a RIFObj))
(defclass AbsRIFTermable (is-a RIFObj));can be used as term
(defclass AbsRIFAtomicFormula (is-a RIFObj));See https://www.w3.org/TR/2013/REC-rif-prd-20130205/#Atomic_formulas

(deftemplate RIFRepresentation
	(slot node)
	(slot object)
)

(defclass RIFConst (is-a AbsRIFTermable))

(defclass RIFConstIRI (is-a RIFConst)
	(slot represents (type LEXEME)))

(defclass RIFConstValue (is-a RIFConst)
	(slot represents (type STRING)))

(defclass RIFLocalValue (is-a RIFConst)
	(slot represents (type STRING)))

(defclass RIFVar (is-a RIFConst)
	(slot varname (type STRING)))

(defclass RIFSlot (is-a RIFObj)
	(slot slotkey) (slot slotvalue))

(defclass RIFForall (is-a AbsRIFSentence)
	(slot vars)
	(slot formula)
	(slot pattern))

(defclass RIFImplies (is-a AbsRIFSentence AbsRIFAction)
	(slot if_) (slot then))

(defclass RIFAnd (is-a AbsRIFPattern AbsRIFCondition)
	(slot formulas))

(defclass RIFOr (is-a AbsRIFCondition)
	(slot formulas))

(defclass RIFAssert (is-a AbsRIFAction)
	(slot target))
(defclass RIFRetract (is-a AbsRIFAction)
	(slot target))
(defclass RIFModify (is-a AbsRIFAction)
	(slot target))
(defclass RIFExecute (is-a AbsRIFAction)
	(slot target))

(defclass RIFAtom (is-a AbsRIFSentence AbsRIFAction AbsRIFPattern AbsRIFAtomicFormula)
	(slot op) (slot args))

(defclass RIFExpr (is-a RIFAtom)
	(slot op) (slot args))

(defclass RIFFrame (is-a AbsRIFSentence AbsRIFAction AbsRIFAtomicFormula)
	(slot object) (slot slots))

(defclass RIFNew (is-a RIFObj))

(defclass RIFMember (is-a AbsRIFSentence AbsRIFAction AbsRIFAtomicFormula)
	(slot instance) (slot class))

(defclass RIFSubclass (is-a AbsRIFSentence AbsRIFAction AbsRIFAtomicFormula)
	(slot sub) (slot super))

(defclass RIFExternal (is-a AbsRIFAction AbsRIFTermable AbsRIFPattern AbsRIFAtomicFormula)
	(slot content))

(defclass RIFEqual (is-a AbsRIFAction AbsRIFPattern)
	(slot left) (slot right))

(defclass RIFExists (is-a AbsRIFAction AbsRIFPattern)
	(slot formula) (slot vars))

(defclass RIFList (is-a RIFConst)
	(slot items))

(defclass RIFDo (is-a AbsRIFAction)
	(slot varinit (default FALSE))
	(multislot actionVars)
	(slot actions)); (type RDFList)

(defclass RIFINeg (is-a AbsRIFCondition AbsRIFPattern)
	(slot formula))

(defclass RIFGroup (is-a RIFObj)
	(slot sentences)
	(slot priority (default 0))
)

(defclass RIFDocument (is-a RIFObj)
	(slot payload) (slot directives))

(defclass RIFImport (is-a RIFObj)
	(slot profile) (slot location))

;# assert RIF placeholder objects

;# RIF placeholder objects functions

;##rules

(defrule RDFWarnOnlyOneRepresentation
	?obj1 <- (object (is-a RDFObj) (node ?x))
	?obj2 <- (object (is-a RDFObj) (node ?y))
	(test (neq ?obj1 ?obj2))
	(test (eq ?x ?y))
	=>
	(println "duplicate representation of " ?x " " ?y)
)

(defrule RDFList_INIT
	(exists (TripleTemplate
                (object <http://www.w3.org/1999/02/22-rdf-syntax-ns#nil>)))
	=>
	(bind ?node <http://www.w3.org/1999/02/22-rdf-syntax-ns#nil>)
	(bind ?x (make-instance of RDFList
		(node ?node)
		(items)))
	(assert (RIFRepresentation (node ?node) (object ?x)))
)

(defrule RDFList_CONTINUE
        (TripleTemplate
                (subject ?rdflist)
                (predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#first>)
                (object ?firstProperty))
        (TripleTemplate
                (subject ?rdflist)
                (predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#rest>)
                (object ?rest))
	?restlist <-(object (node ?rest) (is-a RDFList))
	?firstObj <-(object (node ?firstProperty) (is-a RDFObj))
	=>
	(bind ?newlist (create$ ?firstObj (send ?restlist get-items)))
	(bind ?x (make-instance of RDFList (node ?rdflist) (items ?newlist)))
	(assert (RIFRepresentation (node ?rdflist) (object ?x)))
)

(defrule RIFprocess_New
        (TripleTemplate
                (subject ?node)
		(predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
                (object <http://www.w3.org/2007/rif#New>))
	=>
	(bind ?x (make-instance of RIFNew (node ?node)))
	(assert (RIFRepresentation (node ?node) (object ?x)))
)

(defrule RIFprocess_ConstIRI
        (TripleTemplate
                (subject ?node)
		(predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
                (object <http://www.w3.org/2007/rif#Const>))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#constIRI>)
		(object ?representedNode))
	=>
	(bind ?x (RIFConst_ExtractURI ?representedNode))
	(bind ?x (make-instance of RIFConstIRI (node ?node)
		(represents ?representedNode)))
	(assert (RIFRepresentation (node ?node) (object ?x)))
)

(defrule RIFprocess_LocalValue
        (TripleTemplate
                (subject ?node)
		(predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
                (object <http://www.w3.org/2007/rif#Const>))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#constname>)
		(object ?name))
	=>
	(bind ?x (make-instance of RIFLocalValue (node ?node)
		(represents ?name)))
	(assert (RIFRepresentation (node ?node) (object ?x)))
)

(defrule RIFprocess_ConstValue
        (TripleTemplate
                (subject ?node)
		(predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
                (object <http://www.w3.org/2007/rif#Const>))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#value>)
		(object ?value))
	=>
	(bind ?x (make-instance of RIFConstValue (node ?node)
		(represents ?value)))
	(assert (RIFRepresentation (node ?node) (object ?x)))
)

(defrule RIFprocess_Var
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
		(object <http://www.w3.org/2007/rif#Var>))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#varname>)
		(object ?varname))
	=>
	(bind ?x (make-instance of RIFVar (varname ?varname) (node ?node)))
	(assert (RIFRepresentation (node ?node) (object ?x)))
)

(defrule RIFprocess_Assert
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
		(object <http://www.w3.org/2007/rif#Assert>))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#target>)
		(object ?nodetarget))
	?objtarget <- (object (is-a RIFObj) (node ?nodetarget))
	=>
	(bind ?x (make-instance of RIFAssert (node ?node)
		(target ?objtarget)))
	(assert (RIFRepresentation (node ?node) (object ?x)))
)

(defrule RIFprocess_Modify
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
		(object <http://www.w3.org/2007/rif#Modify>))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#target>)
		(object ?nodetarget))
	?objtarget <- (object (is-a RIFObj) (node ?nodetarget))
	=>
	(bind ?x (make-instance of RIFModify (node ?node)
		(target ?objtarget)))
	(assert (RIFRepresentation (node ?node) (object ?x)))
)

(defrule RIFprocess_Retract
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
		(object <http://www.w3.org/2007/rif#Retract>))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#target>)
		(object ?nodetarget))
	?objtarget <- (object (is-a RIFObj) (node ?nodetarget))
	=>
	(bind ?x (make-instance of RIFRetract (node ?node)
		(target ?objtarget)))
	(assert (RIFRepresentation (node ?node) (object ?x)))
)

(defrule RIFprocess_Execute
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
		(object <http://www.w3.org/2007/rif#Execute>))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#target>)
		(object ?nodetarget))
	?objtarget <- (object (is-a RIFObj) (node ?nodetarget))
	=>
	(bind ?x (make-instance of RIFExecute (node ?node)
		(target ?objtarget)))
	(assert (RIFRepresentation (node ?node) (object ?x)))
)

(defrule RIFprocess_Equal
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
		(object <http://www.w3.org/2007/rif#Equal>))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#left>)
		(object ?nodeleft))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#right>)
		(object ?noderight))
	?objleft <- (object (is-a RIFObj) (node ?nodeleft))
	?objright <- (object (is-a RIFObj) (node ?noderight))
	=>
	(bind ?x (make-instance of RIFEqual (node ?node)
		(left ?objleft) (right ?objright)))
	(assert (RIFRepresentation (node ?node) (object ?x)))
)

(defrule RIFprocess_Exists
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
		(object <http://www.w3.org/2007/rif#Exists>))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#formula>)
		(object ?nodeformula))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#vars>)
		(object ?nodevars))
	?objformula <- (object (node ?nodeformula) (is-a RIFObj))
	?objvars <- (object (node ?nodevars) (is-a RDFList))
	=>
	(bind ?x (make-instance of RIFExists (node ?node)
		(formula ?objformula) (vars ?objvars)))
	(assert (RIFRepresentation (node ?node) (object ?x)))
)

(defrule RIFprocess_List
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
		(object <http://www.w3.org/2007/rif#List>))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#items>)
		(object ?nodeitems))
	?objitems <- (object (is-a RDFObj) (node ?nodeitems))
	=>
	(bind ?x (make-instance of RIFList (node ?node)
		(items ?objitems)))
	(assert (RIFRepresentation (node ?node) (object ?x)))
)


(defrule RIFSlot_init
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
		(object <http://www.w3.org/2007/rif#Slot>))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#slotkey>)
		(object ?slotkeyNode))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#slotvalue>)
		(object ?slotvalueNode))
	?key <- (object (is-a RIFObj) (node ?slotkeyNode))
	?value <- (object (is-a RIFObj) (node ?slotvalueNode))
	=>
	(bind ?x (make-instance of RIFSlot (node ?node)
		(slotkey ?key) (slotvalue ?value)))
	(assert (RIFRepresentation (node ?node) (object ?x)))
)

(defrule RIFprocess_Frame
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
		(object <http://www.w3.org/2007/rif#Frame>))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#object>)
		(object ?object))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#slots>)
		(object ?slots))
	?objobject <- (object (is-a RIFObj) (node ?object))
	?objslots <- (object (is-a RDFObj) (node ?slots))
	=>
	(bind ?x (make-instance of RIFFrame (node ?node)
		(object ?objobject) (slots ?objslots)))
	(assert (RIFRepresentation (node ?node) (object ?x)))
)

(defrule RIFprocess_Subclass
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
		(object <http://www.w3.org/2007/rif#Subclass>))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#sub>)
		(object ?sub))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#super>)
		(object ?super))
	?objsub <- (object (node ?sub) (is-a RIFObj))
	?objsuper <- (object (node ?super) (is-a RDFObj))
	=>
	(bind ?x (make-instance of RIFSubclass (node ?node)
		(sub ?objsub) (super ?objsuper)))
	(assert (RIFRepresentation (node ?node) (object ?x)))
)

(defrule RIFprocess_Member
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
		(object <http://www.w3.org/2007/rif#Member>))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#instance>)
		(object ?instance))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#class>)
		(object ?class))
	?objinstance <- (object (is-a RIFObj) (node ?instance))
	?objclass <- (object (is-a RDFObj) (node ?class))
	=>
	(bind ?x (make-instance of RIFMember (node ?node)
		(instance ?objinstance) (class ?objclass)))
	(assert (RIFRepresentation (node ?node) (object ?x)))
)

(defrule _default_empty_atom_args
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
		(object <http://www.w3.org/2007/rif#Atom>))
	(not (exists (TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#args>))))
	=>
	(assert (TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#args>)
		(object <http://www.w3.org/1999/02/22-rdf-syntax-ns#nil>)))
)

(defrule RIFprocess_Atom
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
		(object <http://www.w3.org/2007/rif#Atom>))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#op>)
		(object ?op))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#args>)
		(object ?args))
	?objop <- (object (is-a RIFObj) (node ?op))
	?objargs <- (object (is-a RDFObj) (node ?args))
	=>
	(bind ?x (make-instance of RIFAtom (node ?node)
		(op ?objop) (args ?objargs)))
	(assert (RIFRepresentation (node ?node) (object ?x)))
)

(defrule RIFprocess_Expr
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
		(object <http://www.w3.org/2007/rif#Expr>))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#op>)
		(object ?op))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#args>)
		(object ?args))
	?objop <- (object (is-a RIFObj) (node ?op))
	?objargs <- (object (is-a RDFObj) (node ?args))
	=>
	(bind ?x (make-instance of RIFExpr (node ?node)
		(op ?objop) (args ?objargs)))
	(assert (RIFRepresentation (node ?node) (object ?x)))
)

(defrule RIFprocess_External
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
		(object <http://www.w3.org/2007/rif#External>))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#content>)
		(object ?content))
	(RIFRepresentation
		(node ?content)
		(object ?objcontent))
	=>
	(bind ?x (make-instance of RIFExternal (node ?node)
		(content ?objcontent)))
	(assert (RIFRepresentation (node ?node) (object ?x)))
)

(defrule RIFprocess_INeg
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
		(object <http://www.w3.org/2007/rif#INeg>))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#formula>)
		(object ?nodeformula))
	?objectformula <- (object (is-a RDFObj) (node ?nodeformula))
	=>
	(bind ?x (make-instance of RIFINeg (node ?node)
		(formula ?objectformula)))
	(assert (RIFRepresentation (node ?node) (object ?x)))
)

	
(defrule RIFprocess_Do
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
		(object <http://www.w3.org/2007/rif#Do>))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#actions>)
		(object ?nodeactions))
	?objectactions <- (object (is-a RDFObj) (node ?nodeactions))
	=>
	(bind ?x (make-instance of RIFDo (node ?node)
		(actions ?objectactions)))
	(assert (RIFRepresentation (node ?node) (object ?x)))
)

(defrule RIFDo_add_actionVar
	?obj <- (object (is-a RIFDo) (node ?node))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#actionVar>)
		(object ?varnode))
	?varlist <- (object (is-a RDFList) (node ?varnode))
	=>
	(slot-insert$ ?obj actionVars 1 ?varlist)
)

(defrule RIFprocess_Forall
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
		(object <http://www.w3.org/2007/rif#Forall>))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#formula>)
		(object ?nodeformula))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#vars>)
		(object ?nodevars))
	?objformula <- (object (is-a RIFObj) (node ?nodeformula))
	?objvars <- (object (is-a RDFList) (node ?nodevars))
	=>
	(make-instance of RIFForall (node ?node)
		(vars ?objvars)
		(formula ?objformula))
)

(defrule RIFprocess_Implies
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
		(object <http://www.w3.org/2007/rif#Implies>))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#if>)
		(object ?nodeif))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#then>)
		(object ?nodethen))
	?objectif <- (object (is-a RIFObj) (node ?nodeif))
	?objectthen <- (object (is-a RIFObj) (node ?nodethen))
	=>
	(bind ?x (make-instance of RIFImplies (node ?node)
		(if_ ?objectif) (then ?objectthen)))
	(assert (RIFRepresentation (node ?node) (object ?x)))
)

(defrule RIFprocess_And
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
		(object <http://www.w3.org/2007/rif#And>))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#formulas>)
		(object ?nodeformulas))
	?objformulas <- (object (is-a RDFList) (node ?nodeformulas))
	=>
	(bind ?x (make-instance of RIFAnd (node ?node)
		(formulas ?objformulas)))
	(assert (RIFRepresentation (node ?node) (object ?x)))
)

(defrule RIFprocess_Or
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
		(object <http://www.w3.org/2007/rif#Or>))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#formulas>)
		(object ?nodeformulas))
	?objformulas <- (object (is-a RDFList) (node ?nodeformulas))
	=>
	(bind ?x (make-instance of RIFOr (node ?node)
		(formulas ?objformulas)))
	(assert (RIFRepresentation (node ?node) (object ?x)))
)

(defrule RIFprocess_Group
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
		(object <http://www.w3.org/2007/rif#Group>))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#sentences>)
		(object ?nodesentences))
	?objsentences <- (object (is-a RDFList) (node ?nodesentences))
	=>
	(bind ?x (make-instance of RIFGroup (node ?node)
		(sentences ?objsentences)))
	(assert (RIFRepresentation (node ?node) (object ?x)))
)

(defrule RIFGroup_add_salience
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#behavior>)
		(object ?behavior))
	(TripleTemplate
		(subject ?behavior)
		(predicate <http://www.w3.org/2007/rif#Priority>)
		(object ?priority))
	?group <- (object (node ?node) (is-a RIFGroup))
	=>
	(send ?group put-priority (<http://www.w3.org/2001/XMLSchema#string> ?priority))
)

;ignore for now
;(defrule RIFGroup_inherit_salience
;	(not
;	(TripleTemplate
;		(subject ?node)
;		(predicate <http://www.w3.org/2007/rif#behavior>)
;		(object ?behavior))
;	(TripleTemplate
;		(subject ?behavior)
;		(predicate <http://www.w3.org/2007/rif#Priority>)
;		(object ?priority))
;	)
;	?group <- (object (node ?node) (is-a RIFGroup))
;	?parentgroup <- (object (node ?parentnode) (is-a RIFGroup))
;	=>
;	(send ?group put-priority ?priority)
;)

(defrule RIFprocess_Import
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
		(object <http://www.w3.org/2007/rif#Import>))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#location>)
		(object ?nodelocation))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#profile>)
		(object ?nodeprofile))
	=>
	(bind ?x (make-instance of RIFImport (node ?node)
		(profile ?nodeprofile) (location ?nodelocation)))
	(assert (RIFRepresentation (node ?node) (object ?x)))
)

(defrule RIFprocess_DocumentA
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
		(object <http://www.w3.org/2007/rif#Document>))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#payload>)
		(object ?nodepayload))
	?objpayload <- (object (is-a RIFObj) (node ?nodepayload))
	(not
		(TripleTemplate
			(subject ?node)
			(predicate <http://www.w3.org/2007/rif#directives>))
	)
	=>
	(bind ?x (make-instance of RIFDocument (node ?node)
		(payload ?objpayload)))
	(assert (RIFRepresentation (node ?node) (object ?x)))
)

(defrule UseImportDirective
	?importobj <- (object (is-a RIFImport) (profile ?profile) (location ?location))
	(not (exists (already-imported ?profile ?location)))
	=>
	(assert (already-imported ?profile ?location))
	(if (not (<http://white.gobo/import> ?location ?profile ))
		then
		(if (not (get-error)) then
			(set-error "<http://white.gobo/import> failed")
		)
	)
)

(defrule RIFprocess_DocumentB
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
		(object <http://www.w3.org/2007/rif#Document>))
	(not
		(TripleTemplate
			(subject ?node)
			(predicate <http://www.w3.org/2007/rif#payload>))
	)
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#directives>)
		(object ?nodedirectives))
	?objdirectives <- (object (is-a RDFList) (node ?nodedirectives))
	=>
	(bind ?x (make-instance of RIFDocument (node ?node)
		(directives ?objdirectives)))
	(assert (RIFRepresentation (node ?node) (object ?x)))
)

(defrule RIFprocess_DocumentC
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
		(object <http://www.w3.org/2007/rif#Document>))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#payload>)
		(object ?nodepayload))
	?objpayload <- (object (is-a RIFObj) (node ?nodepayload))
	(TripleTemplate
		(subject ?node)
		(predicate <http://www.w3.org/2007/rif#directives>)
		(object ?nodedirectives))
	?objdirectives <- (object (is-a RDFList) (node ?nodedirectives))
	=>
	(bind ?x (make-instance of RIFDocument (node ?node)
		(payload ?objpayload) (directives ?objdirectives)))
	(assert (RIFRepresentation (node ?node) (object ?x)))
)


;##methods

(defmessage-handler RIFObj create-binding-in-action (?varname)
	(set-error (str-cat 
		"Missing implementation for create-binding-in-action for " (type ?self)
	))
	(return "")
)

(defmessage-handler RIFObj create-action ()
	;Create a prd style action
	;In clips will be multislot of string representing actions
	(set-error (str-cat 
		"Missing implementation for create-action for " (type ?self)
	))
	(return "")
)

(defmessage-handler AbsRIFAtomicFormula assert-atom-formula ()
	(set-error (str-cat 
		"Missing implementation for assert-atom-formula for " (type ?self)
	))
	(return "")
)

(defmessage-handler RIFObj create-pattern ()
	(set-error (str-cat 
		"Missing implementation for create-pattern for " (type ?self)
	))
	(return ""))

(defmessage-handler RIFObj create-condition ();move this to condition
	(set-error (str-cat 
		"Missing implementation for create-condition for " (type ?self)
	))
	(return ""))

;create action that returns bool
(defmessage-handler RIFObj create-condition ()
	(set-error (str-cat 
		"Missing implementation for create-condition for " (type ?self)
	))
	(return "")
)

(defmessage-handler RIFObj create-sentence (?salience)
	(bind ?name (send ?self get-rulename))
	(bind ?lhs (send ?self get-lhs))
	(if (get-error) then (return ""))
	(bind ?rhs (send ?self get-rhs))
	(bind ?declarations (create$))
	(if (neq 0 ?salience) then
		(bind ?declarations (append$ ?declarations
			(str-cat "(declare (salience "?salience"))")
		))
	)
	(bind ?declarations (str-cat "" (expand$ ?declarations)))
	(return (printrule ?name ?declarations ?lhs ?rhs)))

(defmessage-handler RIFObj get-rulename ()
	(return (str-cat "rule-" (gensym)))
)
(defmessage-handler RIFObj get-rhs ()
	(set-error (str-cat 
		"Missing implementation for get-rhs for " (type ?self)
	))
	(return ""))

(defmessage-handler RIFObj get-lhs ()
	(set-error (str-cat 
		"Missing implementation for get-lhs for " (type ?self)
	))
	(return ""))

(defmessage-handler RIFObj as_term ()
	(set-error (str-cat 
		"Missing implementation for as_term for " (type ?self)
	))
	(return ""))

(defmessage-handler AbsRIFTermable as_term_on_lhs ()
	(make-instance of PatternTerm (term (send ?self as_term))))

(defmessage-handler RIFConstIRI as_term ()
	(bind ?x1 (RDFgetLiteralValue ?self:represents))
	(sym-cat "<" (PercentDecoding ?x1) ">"))

(defmessage-handler RIFConstValue as_term ()
	(return (str-cat "\"" ?self:represents "\"")))

(defmessage-handler RIFLocalValue as_term ()
	(return (sym-cat "_:qq" ?self:represents)))

(defmessage-handler RIFVar as_term () (return (str-cat "?" ?self:varname)))

(deffunction create-test-list (?listvar $?terms)
	(bind ?itemsstr "items")
	(foreach ?x $?terms (bind ?itemsstr ?itemsstr " " ?x))
	(str-cat "(object (name =(instance-name "?listvar")) (is-a list) "
		"("?itemsstr"))"))

(deffunction print-create-list ($?terms)
	(if (eq 0 (length$ $?terms)) then (return "(<http://www.w3.org/2007/rif-builtin-function#make-list>)"))
	(bind ?withspaces (create$))
	(foreach ?t $?terms
		(bind ?withspaces (append$ ?withspaces " " ?t))
	)
	(str-cat "(<http://www.w3.org/2007/rif-builtin-function#make-list>"(expand$ ?withspaces)")")
)

(defmessage-handler RIFList as_term ()
	(bind ?terms (create$))
	(bind ?checks (create$))
	(foreach ?x (send ?self:items get-items)
		(bind ?terms (append$ ?terms (send ?x as_term)))
		(if (get-error) then (return))
	)
	(print-create-list ?terms)
)

(defmessage-handler RIFList as_term_on_lhs ()
	(bind ?listvar (str-cat "?" (gensym)))
	(bind ?terms (create$))
	(bind ?checks (create$))
	(foreach ?x (send ?self:items get-items)
		(bind ?tmp (send ?x as_term_on_lhs))
		(if (get-error) then (return))
		(bind ?terms (append$ ?terms (send ?tmp get-term)))
		(bind ?checks (append$ ?checks (send ?tmp get-checks)))
		(unmake-instance ?tmp)
	)
	(make-instance of PatternTerm
		(term ?listvar)
		(checks ?checks)))


(defmessage-handler RIFForall create-sentence (?salience)
	(if (and (eq nil ?self:pattern) (eq RIFImplies (type ?self:formula)))
		then (return (send ?self:formula create-sentence ?salience)))
	(bind ?name (send ?self get-rulename))
	(bind ?lhs (send ?self get-lhs))
	(bind ?rhs (send ?self get-rhs))
	(return (printrule ?name "" ?lhs ?rhs)))

(defmessage-handler RIFForall get-lhs ()
	(if (neq nil ?self:pattern) then
		(set-error (str-cat 
			"pattern isnt implemented for rifforall get-lhs"
		)))
	(bind ?pattern (create$))
	(foreach ?v (send ?self:vars get-items)
		(bind ?varname (send ?v as_term))
		(bind ?pattern (append$ ?pattern
			(print-anyobjectpattern ?varname)))
	)
	(return (str-cat "" (expand$ ?pattern))))

(defmessage-handler RIFForall get-rhs ()
	(send ?self:formula create-action))

(defmessage-handler RIFImplies create-action ()
	(if (member$ assert-atom-formula (get-defmessage-handler-list
				(type ?self:then) inherit))
		then
		(bind ?action (send ?self:then assert-atom-formula))
		else
		(bind ?action (send ?self:then create-action))
	)
	(bind ?condition (send ?self:if_ create-condition))
	(print-ifthen ?condition ?action)
)

(defmessage-handler RIFImplies get-lhs ()
	(if (neq RIFAnd (type ?self:if_)) then
		(return (send ?self:if_ create-pattern)))
	;else
	(bind ?ret (create$))
	(foreach ?slt (send (send ?self:if_ get-formulas) get-items)
		(bind ?ret (append$ ?ret (send ?slt create-pattern)))
		(bind ?ret (append$ ?ret "
	"))
	)
	(return (str-cat "" (expand$ ?ret)))
)

(defmessage-handler RIFImplies get-rhs ()
	(if (member$ assert-atom-formula (get-defmessage-handler-list
				(type ?self:then) inherit))
		then
		(return (send ?self:then assert-atom-formula))
		else
		(return (send ?self:then create-action))
	)
)

(defmessage-handler RIFAnd create-condition ()
	(bind ?ret (create$))
	(foreach ?slt (send ?self:formulas get-items)
		(bind ?ret (append$ ?ret (send ?slt create-condition)))
		(bind ?ret (append$ ?ret "
	"))
	)
	(if (> (length$ ?ret) 1)
		then (str-cat "(and " (expand$ ?ret) ")")
		else (str-cat "" (expand$ ?ret)))
)

(defmessage-handler RIFAnd create-pattern ()
	(bind ?ret (create$))
	(foreach ?slt (send ?self:formulas get-items)
		(bind ?ret (append$ ?ret (send ?slt create-pattern)))
		(bind ?ret (append$ ?ret "
	"))
	)
	(if (> (length$ ?ret) 1)
		then (str-cat "(and " (expand$ ?ret) ")")
		else (str-cat "" (expand$ ?ret)))
)

(defmessage-handler RIFOr create-pattern ()
	(bind ?ret (create$))
	(foreach ?slt (send ?self:formulas get-items)
		(bind ?ret (append$ ?ret (send ?slt create-pattern)))
		(bind ?ret (append$ ?ret "
	"))
	)
	(if (> (length$ ?ret) 1)
		then (str-cat "(or " (expand$ ?ret) ")")
		else (str-cat "" (expand$ ?ret)))
)

;(defmessage-handler RIFOr create-condition ()
;	(send))

(defmessage-handler RIFNew create-binding-in-action (?varname)
	(return (print-bind-new ?varname))
)

(defmessage-handler RIFFrame create-binding-in-action (?varname)
	(bind ?items (send ?self:slots get-items))
	(if (neq 1 (length$ ?items)) then
		(set-error "during binding in action frames can only have one slot") 
		(return "")
	)
	(bind ?slt (expand$ ?items))
	(bind ?s (send ?self:object as_term))
	(bind ?p (send (send ?slt get-slotkey) as_term))
	(bind ?o (send (send ?slt get-slotvalue) as_term))
        (return (str-cat "(do-for-fact ((?trpl TripleTemplate))
		(and (eq ?trpl:subject "?s") (eq ?trpl:predicate "?p"))
		(bind "?o" ?trpl:object))"))
)

(defmessage-handler RIFDo create-action ()
	(bind ?actions (create$))
	(foreach ?vr ?self:actionVars
		(bind ?x (send ?vr get-items))
		(bind ?varname (send (expand$ (first$ ?x)) as_term))
		(bind ?binder (expand$ (rest$ ?x)))
		(bind ?tmpact (send ?binder create-binding-in-action ?varname))
		(if (get-error) then (return ""))
		;(if (eq (type ?binder) RIFNew)
		;	then
		;		(bind ?tmpact (print-bind-new ?varname))
		;	else
		;		(set-error "frames are not supportin actionVar")
		;		(return "")
		;)
		(bind ?actions (append$ ?actions ?tmpact))
	)
	(foreach ?act (send ?self:actions get-items)
		(bind ?nextact (send ?act create-action))
		(bind ?actions (append$ ?actions ?nextact))
	)
	(str-cat "" (expand$ ?actions))
)

(defmessage-handler RIFDo get-lhs () (return ""))
(defmessage-handler RIFDo get-rhs () (send ?self create-action))

(defmessage-handler RIFAssert create-action ()
	(send ?self:target create-action)
)


(defmessage-handler RIFRetract create-action-atom ()
	(bind ?op (send (send ?self:target get-op) as_term))
	;(bind ?opcondition (str-cat "(eq ?fct:op "?op")"))
	(bind ?tmp "")
	(foreach ?slt (send (send ?self:target get-args) get-items)
		(bind ?tmp (str-cat ?tmp" "(send ?slt as_term)))
	)
	(bind ?args (str-cat "(eq ?fct:args (create$ "?tmp"))"))
	(bind ?factcondition (str-cat "(and (eq ?fct:op "?op") (eq ?fct:args "?args"))"))
	(print-retractatoms ?factcondition)
)

(defmessage-handler RIFRetract create-action-frame ()
	;(eq (type ?self:target) RIFFrame)
	(bind ?frm ?self:target)
	
	(bind ?s (send (send ?self:target get-object) as_term))

	(bind ?predcondition (create$))
	(foreach ?slt (send (send ?self:target get-slots) get-items)
		(bind ?p (send (send ?slt get-slotkey) as_term))
		(bind ?o (send (send ?slt get-slotvalue) as_term))
		(bind ?predcondition (append$ ?predcondition
			(str-cat "(and (eq ?fct:predicate "?p")"
					"(eq ?fct:object "?o"))")))
	)
	(if (eq 1 (length$ ?predcondition))
		then (bind ?predcondition (expand$ ?predcondition))
		else (bind ?predcondition (str-cat "(or "(expand$ ?predcondition)")"))
	)
	(bind ?factcondition (str-cat "(and (eq ?fct:subject "?s") "?predcondition")"))
	(return (print-retracttriples ?factcondition))

)

(defmessage-handler RIFRetract create-action ()
	(bind ?t (type ?self:target))
	(if (or (eq ?t RIFVar) (eq ?t RIFConst)) then
		(return (print-retractsubject (send ?self:target as_term))))
	(if (eq ?t RIFFrame) then
		(return (send ?self create-action-frame)))
	(if (eq ?t RIFAtom) then
		(return (send ?self create-action-atom)))
	(set-error (str-cat "create action not complete implementedin RIFRetract. Missing for target of type " ?t))
	(return "")
)

(defmessage-handler RIFModify create-action ()
	(bind ?t (type ?self:target))
	(if (neq ?t RIFFrame) then
		(set-error "RIF:Modify needs a frame as target.")
		(return ""))
	(bind ?ret (create$))
	(bind ?subj (send (send ?self:target get-object) as_term))
	(foreach ?slt (send (send ?self:target get-slots) get-items)
		(bind ?pred (send (send ?slt get-slotkey) as_term))
		(bind ?ret (append$ ?ret (str-cat
			(print-retractattribute ?subj ?pred)
			(send ?self:target create-action)
		)))
	)
	(return ?ret)
)

(defmessage-handler RIFExecute create-action ()
	(bind ?op (send (send ?self:target get-op) as_term))
	(bind ?args (create$))
	(foreach ?x (send (send ?self:target get-args) get-items)
		(bind ?args (append$ ?args (create$ (send ?x as_term) " "))))
	(print-action ?op (str-cat ""(expand$ ?args)))
)


(defmessage-handler RIFFrame create-sentence (?salience)
	(bind ?name (send ?self get-rulename))
	(bind ?ret (create$))
	(bind ?s (send ?self:object as_term))
	(foreach ?slt (send ?self:slots get-items)
		(bind ?p (send (send ?slt get-slotkey) as_term))
		(bind ?o (send (send ?slt get-slotvalue) as_term))
		(bind ?ret (append$ ?ret (print-triple ?s ?p ?o)))
	)
	(bind ?triples (str-cat "" (expand$ ?ret)))
	(return (print-deffacts ?name ?triples)))

(defmessage-handler RIFFrame create-condition ()
	(bind ?ret (create$))
	(bind ?s (send ?self:object as_term))
	(foreach ?slt (send ?self:slots get-items)
		(bind ?p (send (send ?slt get-slotkey) as_term))
		(bind ?o (send (send ?slt get-slotvalue) as_term))
		(bind ?ret (append$ ?ret (print-triplecondition ?s ?p ?o)))
	)
	(if (> (length$ ?ret) 1)
		then (str-cat "(and " (expand$ ?ret) ")")
		else (str-cat "" (expand$ ?ret)))
)

(defmessage-handler RIFMember create-condition ()
	(bind ?inst (send ?self:instance as_term))
	(bind ?cls (send ?self:class as_term))
	(return (print-membercondition ?inst ?cls))
)

(defmessage-handler RIFSubclass create-condition ()
	(bind ?sub (send ?self:sub as_term))
	(bind ?super (send ?self:super as_term))
	(return (print-subclasscondition ?sub ?super))
)


;return multiple multislots with 3 entries
(defmessage-handler RIFFrame as_triples ()
	(bind ?triples (create$))
	(foreach ?slt (send ?self:slots get-items)
		(bind ?next
			(make-instance of helperfact
				(s (send ?self:object as_term))
				(p (send (send ?slt get-slotkey) as_term))
				(o (send (send ?slt get-slotvalue) as_term))
			)
		)
		(bind ?triples (append$ ?triples ?next))
	)
	(return ?triples)
)

(defmessage-handler RIFFrame get-lhs () (return ""))
(defmessage-handler RIFFrame get-rhs () (send ?self create-action))
(defmessage-handler RIFFrame create-action ()
	(bind ?ret (create$))
	(bind ?s (send ?self:object as_term))
	(foreach ?slt (send ?self:slots get-items)
		(bind ?p (send (send ?slt get-slotkey) as_term))
		(bind ?o (send (send ?slt get-slotvalue) as_term))
		(bind ?ret (append$ ?ret (print-assertTriple ?s ?p ?o)))
	)
	(str-cat "" (expand$ ?ret))
)

(defmessage-handler RIFFrame assert-atom-formula ()
	(bind ?ret (create$))
	(bind ?s (send ?self:object as_term))
	(foreach ?slt (send ?self:slots get-items)
		(bind ?p (send (send ?slt get-slotkey) as_term))
		(bind ?o (send (send ?slt get-slotvalue) as_term))
		(bind ?ret (append$ ?ret (print-assertTriple ?s ?p ?o)))
	)
	(str-cat "" (expand$ ?ret))
)

(defmessage-handler RIFFrame create-pattern ()
	(bind ?ret (create$))
	(bind ?checks (create$))
	(bind ?tmp (send ?self:object as_term_on_lhs))
	(if (get-error) then (return ""))
	(bind ?s (send ?tmp get-term))
	(bind ?checks (append$ ?checks (send ?tmp get-checks)))
	(unmake-instance ?tmp)

	(foreach ?slt (send ?self:slots get-items)
		(bind ?tmp (send (send ?slt get-slotkey) as_term_on_lhs))
		(if (get-error) then (return ""))
		(bind ?p (send ?tmp get-term))
		(bind ?checks (append$ ?checks (send ?tmp get-checks)))
		(unmake-instance ?tmp)

		(bind ?tmp (send (send ?slt get-slotvalue) as_term_on_lhs))
		(if (get-error) then (return ""))
		(bind ?o (send ?tmp get-term))
		(bind ?checks (append$ ?checks (send ?tmp get-checks)))
		(unmake-instance ?tmp)

		(bind ?ret (append$ ?ret (print-triple ?s ?p ?o)))
	)
	(str-cat "" (expand$ ?ret) (expand$ ?checks))
)

(defmessage-handler RIFMember create-pattern ()
	(bind ?ret (create$))

	(bind ?checks (create$))
	(bind ?tmp (send ?self:instance as_term_on_lhs))
	(if (get-error) then (return ""))
	(bind ?inst (send ?tmp get-term))
	(bind ?checks (append$ ?checks (send ?tmp get-checks)))
	(unmake-instance ?tmp)

	(bind ?checks (create$))
	(bind ?tmp (send ?self:class as_term_on_lhs))
	(if (get-error) then (return ""))
	(bind ?cls (send ?tmp get-term))
	(bind ?checks (append$ ?checks (send ?tmp get-checks)))
	(unmake-instance ?tmp)

	(bind ?ret (append$ ?ret (print-member ?inst ?cls)))

	(str-cat "" (expand$ ?ret) (expand$ ?checks))
)

(defmessage-handler RIFMember assert-atom-formula ()
	(bind ?inst (send ?self:instance as_term))
	(bind ?cls (send ?self:class as_term))
	(print-assert (print-member ?inst ?cls)))
(defmessage-handler RIFMember create-action () (send ?self assert-atom-formula))

(defmessage-handler RIFAtom create-sentence (?salience)
	(bind ?name (send ?self get-rulename))
	(bind ?op (send ?self:op as_term))
	(bind ?args (create$))
	(foreach ?x (send ?self:args get-items)
		(bind ?args (append$ ?args (create$ (send ?x as_term) " "))))
	(bind ?qq (str-cat "" (expand$ ?args)))
	(bind ?atoms (print-atom ?op ?qq))
	(return (print-deffacts ?name ?atoms)))

(defmessage-handler RIFAtom create-action ()
	(bind ?op (send ?self:op as_term))
	(bind ?args (create$))
	(foreach ?x (send ?self:args get-items)
		(bind ?args (append$ ?args (create$ (send ?x as_term) " "))))
	(print-assert (print-atom ?op (str-cat "" (expand$ ?args)))))

(defmessage-handler RIFAtom assert-atom-formula ()
	(bind ?op (send ?self:op as_term))
	(bind ?args (create$))
	(foreach ?x (send ?self:args get-items)
		(bind ?args (append$ ?args (create$ (send ?x as_term) " "))))
	(print-assert (print-atom ?op (str-cat "" (expand$ ?args)))))

(defmessage-handler RIFAtom create-pattern ()
	(bind ?checks (create$))

	(bind ?tmp (send ?self:op as_term_on_lhs))
	(if (get-error) then (return ""))
	(if (neq PatternTerm (type ?tmp)) then (set-error "create-pattern of rifatom failed because operant is no patternterm") (return))
	(bind ?op (send ?tmp get-term))
	(bind ?checks (append$ ?checks (send ?tmp get-checks)))
	(unmake-instance ?tmp)

	(bind ?args (create$))
	(foreach ?x (send ?self:args get-items)
		(bind ?tmp (send ?x as_term_on_lhs))
		(if (get-error) then (return ""))
		(bind ?args (append$ ?args (create$ (send ?tmp get-term) " ")))
		(bind ?checks (append$ ?checks (send ?tmp get-checks)))
		(unmake-instance ?tmp))
	(print-atom ?op (str-cat "" (expand$ ?args))))

(defmessage-handler RIFAtom create-condition ()
	(bind ?op (send ?self:op as_term))
	(bind ?argiter (send ?self:args get-items))
	(bind ?args (create$))
	(foreach ?x ?argiter
		(bind ?args (append$ ?args (send ?x as_term)))
	)
	(print-atomcondition ?op ?args))

(defmessage-handler RIFExternal as_term ()
	(bind ?op (send (send ?self:content get-op) as_term))
	(bind ?args (create$))
	(foreach ?x (send (send ?self:content get-args) get-items)
		(bind ?args (append$ ?args (create$ (send ?x as_term) " "))))
	(print-action ?op (str-cat ""(expand$ ?args))))

(defmessage-handler RIFExternal create-pattern ()
	(bind ?op (send (send ?self:content get-op) as_term))

	(bind ?args (create$))
	(foreach ?x (send (send ?self:content get-args) get-items)
		(bind ?args (append$ ?args (create$ (send ?x as_term) " "))))
	(str-cat "(test "(print-action ?op (str-cat ""(expand$ ?args)))")"))

(defmessage-handler RIFEqual create-pattern ()
	(bind ?op "eq")
	(bind ?left (send ?self:left as_term))
	(bind ?right (send ?self:right as_term))
	(bind ?args (create$ ?left ?right))
	(str-cat "(test "(print-action ?op (str-cat ""(expand$ ?args)))")"))

(defmessage-handler RIFExists create-pattern ()
	(str-cat "(exists " (send ?self:formula create-pattern) ")"))

(defmessage-handler RIFExists create-condition ()
	(if (eq (type ?self:formula) RIFFrame) then
		(return (send ?self create-condition-frame))
	)
	(set-error (str-cat "RIFExists cant handle "(type ?self:formula) " in create-condition"))
	(return "")
)

(defmessage-handler RIFExists create-condition-frame ()
	(if (neq 1 (length$ (send (send ?self:formula get-slots) get-items))) then 
		(set-error "only single frames implemented for Exists")
		(return ""))

	(bind ?unbound (create$))
	(foreach ?x (send ?self:vars get-items)
		(bind ?unbound (append$ ?unbound (send ?x as_term))))
	;(if member$ ?unbound asdf)
	(bind ?frame ?self:formula)
	(bind ?ret (create$))
	(bind ?s (send (send ?frame get-object) as_term))
	(if (member$ ?s ?unbound) then (bind ?s nil))
	(foreach ?slt (send (send ?frame get-slots) get-items)
		(bind ?p (send (send ?slt get-slotkey) as_term))
		(if (member$ ?p ?unbound) then (bind ?p nil))
		(bind ?o (send (send ?slt get-slotvalue) as_term))
		(if (member$ ?o ?unbound) then (bind ?o nil))
		(bind ?ret (append$ ?ret (print-triplecondition ?s ?p ?o)))
	)
	(return (str-cat "" (expand$ ?ret)))
)

(defmessage-handler RIFINeg create-pattern ()
	(bind ?t (type ?self:formula))
	(if (eq ?t RIFFrame) then
		(bind ?ret (create$))
		(bind ?s (send (send ?self:formula get-object) as_term))
		(foreach ?slt (send (send ?self:formula get-slots) get-items)
			(bind ?p (send (send ?slt get-slotkey) as_term))
			(bind ?o (send (send ?slt get-slotvalue) as_term))
			(bind ?ret (append$ ?ret (print-neg (print-triple ?s ?p ?o))))
		)
		(return (str-cat ""(expand$ ?ret)))
	)
	(if (eq ?t RIFExists) then
		(return (str-cat "(not" (send ?self:formula create-pattern) ")"))
	)
	(if (eq ?t RIFAnd) then
		(return (str-cat "(not" (send ?self:formula create-pattern) ")"))
	)
	(if (eq ?t RIFMember) then
		(return (str-cat "(not" (send ?self:formula create-pattern) ")"))
	)
	(if (eq ?t RIFExternal) then
		(return (str-cat "(not" (send ?self:formula create-pattern) ")"))
	)
	(set-error (str-cat "create-pattern in rifineg not implemented for " ?t))
	(return "")
)

(defmessage-handler RIFImport create-rules ()
	(return "")
	;(return (<http://white.gobo/ResourceManager/import> ?self:location ?self:profile))
	;(return "")
	(if (not (<http://white.gobo/import> ?self:location ?self:profile ))
		then
		(if (not (get-error)) then
			(set-error "<http://white.gobo/import> failed")
		)
	)
	(return "")
)

(defmessage-handler RIFGroup create-rules ()
	(bind ?ret (create$ ";autogenerated group rules
"))
	(foreach ?sntc (send ?self:sentences get-items)
		(if (eq RIFGroup (type ?sntc))
			then
			(bind ?ret (append$ ?ret (send ?sntc create-rules)))
			else
			(bind ?sntcRet (send ?sntc create-sentence ?self:priority))
			(bind ?ret (append$ ?ret ?sntcRet))
			(bind ?ret (append$ ?ret "
"))
		)
	)
	(str-cat ""(expand$ ?ret))
)

(defmessage-handler RIFDocument create-rules ()
	(bind ?additionalrules (create$))
	(if (neq ?self:directives nil) then
	(foreach ?imp (send ?self:directives get-items)
		(bind ?additionalrules (append$ ?additionalrules
			(send ?imp create-rules)
		))
		(if (get-error) then (return ""))
	))
	(if (neq ?self:payload nil) then
		then (return (str-cat
			(expand$ ?additionalrules)
			(send ?self:payload create-rules)))
		else (return (str-cat (expand$ ?additionalrules)))
	)
)


(deffunction create-rule-halt-when-statement (?name)
	(bind ?pattern (create$))
	(bind ?rhs "(assert (success)) (halt)")
	(do-for-all-facts ((?repr RIFRepresentation))
		(eq (create$) (find-fact
			((?trpl TripleTemplate))
			(eq ?trpl:object ?repr:node)))
		(bind ?pattern (append$ ?pattern
			(send ?repr:object create-pattern)))
		(bind ?err (clear-error))
		(if ?err then
			(println "caught errors during "
					"create-clips-script: " ?err)
			(return "")
		)
	)
	(bind ?lhs (str-cat ""(expand$ ?pattern)))
	(return (printrule ?name "(declare (salience 100))" ?lhs ?rhs))
)

(deffunction create-script-rif-statement (?description)
	(bind ?err (get-error))
	(if ?err then
		(println "clips in error state: " ?err)
		(return "")
	)
	;replace newline with commented newlines:
	(bind ?desc (str-cat ";" ?description))
	(bind ?desc (str-replace ?desc "
" "
;"))
	(bind ?templates "")
	(bind ?conditions (create$))

	(do-for-all-facts ((?repr RIFRepresentation))
		(eq (create$) (find-fact
			((?trpl TripleTemplate))
			(eq ?trpl:object ?repr:node)))
		(if (member$ create-condition (get-defmessage-handler-list
					(type ?repr:object) inherit))
		then
			(bind ?cndt (send ?repr:object create-condition))
			(bind ?conditions (append$ ?conditions ?cndt))
			(bind ?err (clear-error))
			(if ?err then
				(println "caught errors during "
						"create-clips-script: " ?err)
				(return "")
			)
		else
			(bind ?message (str-cat "cant check statementtype "
				(type ?repr:object) " for node " ?repr:node))
			(println ?message)
			(set-error ?message)
			(return "")
		)
	)
	(bind ?action (str-cat "(return " (print-and ?conditions) ")"))
	(bind ?script (print-script check-statements ?action))
	; (send ?qq get-node)(send)
	
	(bind ?rules (create-rule-halt-when-statement "<http://white.gobo/success>"))
	(bind ?err (clear-error))
	(if ?err then
		(facts)
		(instances)
		(println "Cant create clips script to check statement. "
			"Cause: " ?err)
		(return)
	)
	(str-cat ?desc "
" ?templates "
" ?script "
" ?rules "
")
)

(deffunction print-missing-constructs ()
	;(bind ?all_rif_types (create$ <http://www.w3.org/2007/rif#Execute>))
	(do-for-all-facts ((?f TripleTemplate)) (and
		(eq ?f:predicate <http://www.w3.org/1999/02/22-rdf-syntax-ns#type>)
		;(member$ ?f:object (create$))
		(eq 0 (length$ (find-instance ((?repr RIFObj)) (eq ?repr:node ?f:subject)))))
		(println (str-cat "missing representation for node " ?f:subject " of type " ?f:object))
)
)

(deffunction create-script-rif-logic (?description)
	(bind ?err (get-error))
	(if ?err then
		(println "caught errors before create-clips-script: " ?err)
		(return)
	)
	;replace newline with commented newlines:
	(bind ?desc (str-cat ";" ?description))
	(bind ?desc (str-replace ?desc "
" "
;"))
	(bind ?templates "")
	(bind ?rules (create$))
	(do-for-all-instances ((?doc RIFDocument)) TRUE
		;(println "create clips subscript for " ?doc)
		(bind ?rules (insert$ ?rules (+ 1 (length$ ?rules)) (send ?doc create-rules)))
	)
	(if (eq 0 (length$ ?rules)) then 
		(print-missing-constructs)
		(facts)
		(println "no rules created.")
		(return ""))
	(bind ?err (clear-error))
	(if ?err then
		(println "caught errors during create-clips-script: " ?err)
		(return "")
	)
	(str-cat ?desc "
" ?templates "
" (expand$ ?rules))
)

