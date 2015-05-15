app.controller('mypoints', [
    '$scope',
    '$location',
    '$rootScope',
    '$http',
    function ($scope, $location, $rootScope, $http) {

        /*
        Stap1: functie Init
        --------------------
        */

        var init = function () {
            console.log("My Points controller started");
            processDataPoints();
        };

        /*
        Stap2: Controller vars (niet in scope!)
        ------------------------------------------
        */

        var youtubeTimer;

        /*
        Stap3: Controller functions (niet in scope!)
        --------------------------------------------
        */

        var processDataPoints = function () {
            try {
                var newUrl = app.serviceUrl + "Exercises";
                //console.log(newUrl);
                $http.get(newUrl).
                    success(function (data, status, headers, config) {
                        // this callback will be called asynchronously
                        $scope.AllExercises = data;
                    }).
                    error(function (data, status, headers, config) {
                        // called asynchronously if an error occurs
                        // or server returns response with an error status.
                        console.dir("FAILED: Data returned from AllExercises\n" + data);
                    });

            } catch (e) {
                console.log("FAILED Catched: " + e);
            }
        };

        var videoEnded = function() {
            console.log("Show Popup");
            $rootScope.activeMember.GamePoints = parseInt($scope.currentVideo.Points) + parseInt($rootScope.activeMember.GamePoints);
            bootbox.hideAll();
            var congrats = "<h3 class='text-center'>You've earned<br /><span class='label label-success'>+ " + $scope.currentVideo.Points + "</span> Points!</h3>";
            bootbox.dialog({
                title: "<h1 class='text-center'>Congratulations!</h1>",
                message: congrats,
                buttons: {
                    success: {
                        label: "Oh yeah!",
                        className: "btn-success"
                    }
                }
            });
        };

        /*
        Stap4: Scope vars
        ------------------
        */

        $scope.AllExercises = new Array();
        $scope.MyPoints = $rootScope.activeMember.GamePoints;

        /* Stap5: Scope functions
        -------------------------
        */

        $scope.DoExercise = function (id) {
            $scope.currentVideo = $scope.AllExercises[id];
            var intervalTime = ($scope.currentVideo.StopSeconds - $scope.currentVideo.StartSeconds + 5) * 1000; //Added 5sec for loading in the beginning.
            youtubeTimer = setTimeout(function() { videoEnded() }, intervalTime);
            var iframeCreate = "<iframe width=\"868\" height=\"488\" src=\"//www.youtube.com/embed/" + $scope.currentVideo.Url + "?rel=0&autoplay=1&start=" + $scope.currentVideo.StartSeconds + "&end=" + $scope.currentVideo.StopSeconds + "&controls=0&iv_load_policy=3&disablekb=1&theme=light&color=white\" frameborder=\"0\" style=\"pointer-events: none;\" allowfullscreen></iframe>";
            bootbox.dialog({
                closeButton: false,
                title: $scope.currentVideo.Name,
                message: iframeCreate,
                size: "large",
                buttons: {
                    danger: {
                        label: "Stop Exercise",
                        className: "btn-default",
                        callback: function() {
                            console.log("Video Stopped by User");
                            window.clearTimeout(youtubeTimer);
                        }
                    }
                }
            });
        };

        /* Stap6: init aanroepen
        --------------------
        */
        init();

    }]);