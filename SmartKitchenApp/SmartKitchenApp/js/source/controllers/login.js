app.controller('login', [
    '$scope',
    '$location',
    '$rootScope',
    'loginservice',
    function ($scope, $location, $rootScope, loginservice) {

        /*
        Stap1: functie Init
        --------------------
        */

        // hier kan je zaken doen die ALTIJD moeten gebeuren bij het inladen van deze pagina, bijvoorbeeld: config ophalen, user checken en ophalen, een of andere call naar service met info... getNumberOfRegisterdUsers ofzo...

        var init = function () {
            console.log('login controller started');
        };

        /*
        Stap2: Controller vars (niet in scope!)
        ------------------------------------------
        */


        /*
        Stap3: Controller functions (niet in scope!)
        --------------------------------------------
        */


        /*
        Stap4: Scope vars
        ------------------
        */


        /* Stap5: Scope functions
        -------------------------
        */


        /* Stap6: init aanroepen
        --------------------
        */
        init();

    }]);