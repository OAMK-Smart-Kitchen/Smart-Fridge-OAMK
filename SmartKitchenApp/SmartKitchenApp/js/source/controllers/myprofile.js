app.controller('myprofile', [
    '$scope',
    '$rootScope',
    'memberservice',
    function ($scope, $rootScope, memberservice) {

        /*
        Stap1: functie Init
        --------------------
        */

        var init = function () {
            console.log("myprofile controller started");
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

        $scope.editedMember = new app.Member(); //$rootScope.activeMember
        $scope.editedMember = $rootScope.activeMember;
        $scope.editedMember.GameActivated = "true";
        $scope.editStatus = "0";

        /* Stap5: Scope functions
        -------------------------
        */

        $scope.editProfile = function (isValid) {
            if (isValid) {
                $scope.editStatus = "1";
                console.log("New credentials:");
                console.dir($scope.editedMember);
                // Save the new member information and push to server
                $rootScope.activeMember = $scope.editedMember;
                memberservice.updateProfile({
                    'id': $scope.editedMember.Id,
                    'Firstname': $scope.editedMember.Firstname,
                    'Lastname': $scope.editedMember.Lastname,
                    'DateOfBirth': $scope.editedMember.DateOfBirth,
                    'Email': $scope.editedMember.Email,
                    'Active': $scope.editedMember.Active,
                    'DefaultColor': $scope.editedMember.DefaultColor,
                    'GameActivated': $scope.editedMember.GameActivated,
                    'GamePoints': $scope.editedMember.GamePoints
                })
                 .$promise
                        .then(function onSuccess(data) {
                            // Update list of all members
                            for (var i in $scope.allMembers) {
                                if ($scope.allMembers[i].Id == $scope.editedMember.Id) {
                                    $scope.allMembers[i] = $scope.editedMember;
                                    break; //Stop this loop, we found it!
                                }
                            }
                            // Data stored successfull
                            $scope.editStatus = "0";
                            bootbox.hideAll();
                            bootbox.dialog({
                                title: "<h1 class='text-center'>Hooray!!</h1>",
                                message: "<h2 class='text-center'><i class='fa fa-thumbs-o-up'></i>&nbsp; Your profile has been updated successfully.</h2>",
                                buttons: {
                                    success: {
                                        label: "Thanks!",
                                        className: "btn-success"
                                    }
                                }
                            });
                        }, function onFail(data) {
                            // Something went wrong
                            console.log("FAILED: Data Return from Edit Members Profile");
                            console.dir(data);
                        });
            }
        };


        /* Stap6: init aanroepen
        --------------------
        */
        init();

    }]);