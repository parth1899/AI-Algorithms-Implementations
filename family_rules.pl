% Facts: parent, male, female, married,  

% Grandparent Rule
grandparent(X, Y) :- parent(X, Z), parent(Z, Y).

% Great Grandparent Rule
greatgrandparent(X, Y) :- grandparent(X, Z), parent(Z, Y).

% Mother and Father
father(X, Y) :- parent(X, Y), male(X).
mother(X, Y) :- parent(X, Y), female(X).

son(X, Y) :- parent(Y, X), male(X).   % X is a son of Y if Y is a parent of X and X is male.
daughter(X, Y) :- parent(Y, X), female(X). % X is a daughter of Y if Y is a parent of X and X is female.

% Grandfather and Grandmother
grandfather(X, Y) :- grandparent(X, Y), male(X).
grandmother(X, Y) :- grandparent(X, Y), female(X).

% Great Grandfather and Great Grandmother
greatgrandfather(X, Y) :- greatgrandparent(X, Y), male(X).
greatgrandmother(X, Y) :- greatgrandparent(X, Y), female(X).


% Sibling Rule
sibling(X, Y) :- parent(Z, X), parent(Z, Y), X \= Y.

% Brother and Sister
brother(X, Y) :- sibling(X, Y), male(X).
sister(X, Y) :- sibling(X, Y), female(X).


% Uncle and Aunt
uncle(X, Y) :- brother(X, Z), parent(Z, Y).
aunt(X, Y) :- sister(X, Z), parent(Z, Y).

% Cousin Rule (First Cousins)
cousin(X, Y) :- parent(P1, X), parent(P2, Y), sibling(P1, P2), X \= Y.

% Second Cousin Rule (Same Generation)
second_cousin(X, Y) :- grandparent(GP1, X), grandparent(GP2, Y), sibling(GP1, GP2), X \= Y.


% Husband Rule: X is the husband of Y if X is married to Y and X is male
husband(X, Y) :- married(X, Y), male(X).


% Wife Rule: X is the wife of Y if X is married to Y and X is female
wife(X, Y) :- married(X, Y), female(X).


% Second Uncle Rule (Male cousin of your parent)
second_uncle(X, Y) :-
    parent(P, Y),                % P is the parent of Y
    cousin(X, P),                % X is a cousin of P
    male(X).                     % X is male

    % Second Aunt Rule (Female cousin of your parent)
second_aunt(X, Y) :-
    parent(P, Y),                % P is the parent of Y
    cousin(X, P),                % X is a cousin of P
    female(X).                   % X is female

% Second Grandfather Rule (Brother of your grandparent or husband of second grandmother)
second_grandfather(X, Y) :-
    grandparent(GP, Y),           % GP is a grandparent of Y
    brother(X, GP).               % X is the brother of GP (i.e., second grandfather)

second_grandfather(X, Y) :-
    second_grandmother(SGM, Y),   % SGM is the second grandmother of Y
    husband(X, SGM).              % X is the husband of SGM (i.e., second grandfather)

% Second Grandmother Rule (Sister of your grandparent)
second_grandmother(X, Y) :-
    grandparent(GP, Y),           % GP is a grandparent of Y
    sister(X, GP).                % X is the sister of GP (i.e., second grandmother)


nephew(X, Y) :- male(X), parent(Z, X), sibling(Z, Y).
niece(X, Y) :- female(X), parent(Z, X), sibling(Z, Y).

son_in_law(X, Y) :- male(X), married(X, Z), parent(Y, Z), female(Z).
father_in_law(X, Y) :- male(X), parent(X, Z), married(Z, Y).
daughter_in_law(X, Y) :- female(X), married(X, Z), parent(Y, Z), male(Z).
mother_in_law(X, Y) :- female(X), parent(X, Z), married(Z, Y).

second_nephew(X, Y) :- male(X), parent(Z, X), cousin(Z, Y).
second_niece(X, Y) :- female(X), parent(Z, X), cousin(Z, Y).

third_nephew(X, Y) :- male(X), parent(Z, X), second_cousin(Z, Y).
