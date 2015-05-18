app.controller('products', [
    '$scope',
    '$location',
    '$http',
    'fridgeproductsservice',
    function ($scope, $location, $http, fridgeproductsservice) {

        /*
        Stap1: functie Init
        --------------------
        */

        var init = function () {
            console.log("products controller started");
            processData();
            reloadDate = setInterval(function () { processData() }, 3000);
        };

        /*
        Stap2: Controller vars (niet in scope!)
        ------------------------------------------
        */

        var reloadDate;

        /*
        Stap3: Controller functions (niet in scope!)
        --------------------------------------------
        */

        var processData = function() {
            try {
                var newUrl = app.serviceUrl + "Fridge/Products/" + app.CurrentKitchen.Id;
                console.log(newUrl);
                $http.get(newUrl).
                    success(function(data, status, headers, config) {
                        // this callback will be called asynchronously
                        $scope.AllFridgeProducts = data;
                    }).
                    error(function(data, status, headers, config) {
                        // called asynchronously if an error occurs
                        // or server returns response with an error status.
                        console.dir("FAILED: Data returned from AllFridgeProducts\n" + data);
                    });

            } catch (e) {
                console.log("FAILED Catched: " + e);
            }
        };

        /*
        Stap4: Scope vars
        ------------------
        */

        $scope.AllFridgeProducts = [];

        /* Stap5: Scope functions
        -------------------------
        */

       
        /* Stap6: init aanroepen
        --------------------
        */
        init();

    }]);