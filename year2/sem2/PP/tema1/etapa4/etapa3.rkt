#lang racket

(require "etapa2.rkt")

(provide (all-defined-out))

; TODO 1
; După modelul funcției stable-match?, implementați funcția
; get-unstable-couples care primește o listă de logodne
; engagements, o listă de preferințe masculine mpref și o 
; listă de preferințe feminine wpref, și întoarce lista
; tuturor cuplurilor instabile din engagements.
; Precizări (aspecte care se garantează, nu trebuie verificate):
; - fiecare cuplu din lista engagements are pe prima poziție
;   o femeie
; Nu este permisă recursivitatea pe stivă.
; Nu sunt permise alte funcții ajutătoare decât
; better-match-exists? și funcțiile de manipulare a listelor de
; preferințe definite în etapele anterioare.
; Nu este permisă apelarea multiplă a aceleiași funcții pe
; aceleași argumente.
; Folosiți una sau mai multe dintre expresiile let, let*, letrec,
; named let pentru a vă putea conforma acestor restricții.

(define (get-unstable-couples engagements mpref wpref)
  (let ((reverse-engagements (map (λ (pair) (cons (cdr pair) (car pair))) engagements)))
    (let parse-engagements ((engs engagements) (result '()))
      (if (null? engs)
          result
          (let* ((couple (car engs)) (girl (car couple)) (boy (cdr couple)) (rest-of-list (cdr engs)))
            (if (or (better-match-exists? boy  girl (get-pref-list mpref boy)  wpref engagements)
                    (better-match-exists? girl boy  (get-pref-list wpref girl) mpref reverse-engagements))
                (parse-engagements rest-of-list (cons couple result))
                (parse-engagements rest-of-list result)
                )
            )
          )
      )
    )
  )

; TODO 2
; Implementați funcția engage care primește o listă free-men
; de bărbați încă nelogodiți, o listă de logodne parțiale 
; engagements (unde fiecare cuplu are pe prima poziție o femeie),
; o listă de preferințe masculine mpref și o listă de preferințe 
; feminine wpref, și întoarce o listă completă de logodne stabile,
; obținută conform algoritmului Gale-Shapley:
; - cât timp există un bărbat m încă nelogodit
;   - w = prima femeie din preferințele lui m pe care m nu a cerut-o încă
;   - dacă w este nelogodită, adaugă perechea (w, m) la engagements
;   - dacă w este logodită cu m'
;     - dacă w îl preferă pe m lui m'
;       - m' devine liber
;       - actualizează partenerul lui w la m în engagements
;     - altfel, repetă procesul cu următoarea femeie din lista lui m
; Folosiți named let pentru orice proces recursiv ajutător (deci nu
; veți defini funcții ajutătoare recursive).
; Folosiți let și/sau let* pentru a evita calcule duplicate.
(define (engage free-men engagements mpref wpref)
  (let parse-free-men ((remaining-free-men free-men) (result engagements))
    (if (null? remaining-free-men)
        result
        (let* ((current (car remaining-free-men)) (pref-list (get-pref-list mpref current)))
          (let parse-pref-list ((prefs pref-list))
            (let* ((woman (car prefs)) (woman-partner (get-partner result woman)) (new-couple (cons woman current)) (rest-of-list (cdr remaining-free-men)))
              (cond ((not woman-partner)
                     (parse-free-men rest-of-list (cons new-couple result)))
                    ((preferable? (get-pref-list wpref woman) current woman-partner)
                     (parse-free-men (cons woman-partner rest-of-list) (update-engagements result woman current)))
                    (else (parse-pref-list (cdr prefs)))
                    )
              )
            )
          )
        )
    )
  )

; TODO 3
; Implementați funcția gale-shapley care este un wrapper pentru
; algoritmul implementat de funcția engage. Funcția gale-shapley
; primește doar o listă de preferințe masculine mpref și o listă
; de preferințe feminine wpref și calculează o listă completă de
; logodne stabile conform acestor preferințe.
(define (gale-shapley mpref wpref)
  (engage (get-men mpref) '() mpref wpref)
  )


; TODO 4
; Implementați funcția get-couple-members care primește o listă
; de perechi cu punct și întoarce o listă simplă cu toate elementele 
; care apar în perechi.
; Folosiți funcționale, fără recursivitate explicită.
(define (get-couple-members pair-list)
  (foldr (λ (pair acc)
           (cons (car pair) (cons (cdr pair) acc))
           )
         '()
         pair-list)
  )

