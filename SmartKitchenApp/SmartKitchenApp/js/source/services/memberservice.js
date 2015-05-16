app.service('memberservice', [
    '$resource',
    function ($resource) {
        var MemberService = $resource(app.serviceUrl, { id: '@id' }, {
            Login: {
                url: app.serviceUrl + 'Kitchen/Login',
                method: "POST",
                headers: {
                    'Content-Type': 'application/json'
                },
                params: {
                    Email: '@email',
                    Password: '@password',
                }
            },
            Register: {
                url: app.serviceUrl + 'Kitchen/Register',
                method: "POST",
                headers: {
                    'Content-Type': 'application/json'
                },
                params: {
                    KitchenName: '@kitchenname',
                    Firstname: '@firstname',
                    Lastname: '@lastname',
                    DateOfBirth: '@dateofbirth',
                    Email: '@email',
                    Password: '@password',
                    Active: '@active',
                    Admin: '@admin'
                }
            },
            AddMember: {
                url: app.serviceUrl + 'Kitchen/Member/:id',
                method: "POST",
                headers: {
                    'Content-Type': 'application/json'
                },
                params: {
                    Firstname: '@firstname',
                    Lastname: '@lastname',
                    DateOfBirth: '@dateofbirth',
                    Email: '@email',
                    Password: '@password',
                    Active: '@active',
                    Admin: '@admin'
                }
            },
            UpdateProfile: {
                url: app.serviceUrl + 'Member/Profile/:id',
                method: 'PUT',
                headers: {
                    'Content-Type': 'application/json'
                },
                params: {
                    Firstname: '@firstname',
                    Lastname: '@lastname',
                    DateOfBirth: '@dateofbirth',
                    Email: '@email',
                    DefaultColor: '@defaultcolor',
                    Active: '@active',
                    GameActivated: '@gameactivated',
                    GamePoints: '@gamepoints'
                }
            },
            AddMemberLength: {
                url: app.serviceUrl + 'Kitchen/Member/Length/:id',
                method: "POST",
                headers: {
                    'Content-Type': 'application/json'
                },
                params: {
                    Value: '@value'
                }
            },
            AddMemberWeight: {
                url: app.serviceUrl + 'Kitchen/Member/Weight/:id',
                method: "POST",
                headers: {
                    'Content-Type': 'application/json'
                },
                params: {
                    Value: '@value'
                }
            },
            ForgotPassword: {
                url: app.serviceUrl + 'Members/ForgotPassword',
                method: "POST",
                headers: {
                    'Content-Type': 'application/json'
                },
                params: {
                    data: '@member'
                }
            }

        }
        );

        var API = {
            memberLogin: MemberService.Login,
            memberRegister: MemberService.Register,
            addMember: MemberService.AddMember,
            updateProfile: MemberService.UpdateProfile,
            addMemberLength: MemberService.AddMemberLength,
            addMemberWeight: MemberService.AddMemberWeight,
            memberForgotPassword: MemberService.ForgotPassword
        };

        return API;
    }
]);