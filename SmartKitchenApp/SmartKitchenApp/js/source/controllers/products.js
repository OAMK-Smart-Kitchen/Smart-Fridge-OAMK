app.controller('products', [
    '$scope',
    '$location',
    '$rootScope',
    function ($scope, $location, $rootScope) {

        /*
        Stap1: functie Init
        --------------------
        */

        var init = function () {
            console.log("products controller started");
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

        $scope.AllFridgeProducts = new Array();

        /* Stap5: Scope functions
        -------------------------
        */
        

       
        /* Stap6: init aanroepen
        --------------------
        */
        init();

    }]);
